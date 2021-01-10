#include "Foundation/IPC/BoundedBuffer.h"
#include "boost/interprocess/managed_shared_memory.hpp"

namespace Foundation {
namespace IPC {


    BoundedBuffer::BoundedBuffer(const std::string & memoryName)
        : AbstractBuffer(memoryName),
          _objectSpaceName(memoryName + SHARED_OBJECT_SUFFIX)
    {}

    BoundedBuffer::BoundedBuffer(const std::string & memoryName, unsigned int memorySize)
        : AbstractBuffer(memoryName, memorySize),
          _objectSpaceName(memoryName + SHARED_OBJECT_SUFFIX)
    {
        BoundingSharedState::create(_objectSpaceName);
    }

    BoundedBuffer & BoundedBuffer::operator=(BoundedBuffer && other) noexcept
    {
        if (this == &other)
            return *this;

        *this = other;
        return *this;
    }

    BoundedBuffer & BoundedBuffer::operator=(const BoundedBuffer & other)
    {
        if (this == &other)
            return *this;

        *this = other;
        return *this;
    }

    void BoundedBuffer::clear()
    {
        auto readWriteMode = boost::interprocess::read_write;
        boost::interprocess::shared_memory_object sharedMemoryObject(
                boost::interprocess::open_only,
                _objectSpaceName.c_str(),
                readWriteMode
            );

        sharedMemoryObject.truncate(sizeof(BoundingSharedState));
        boost::interprocess::mapped_region mappedRegion(sharedMemoryObject, readWriteMode);
        auto mappedRegionAddress = mappedRegion.get_address();
        auto sharedState = static_cast<BoundingSharedState *>(mappedRegionAddress);

        AbstractBuffer::clear();
        sharedState->write.notify_one();
        sharedState->bufferEmpty = true;
    }

    void BoundedBuffer::destroy()
    {
        AbstractBuffer::destroy();
        BoundingSharedState::destroy(_objectSpaceName);
    }

    std::string BoundedBuffer::get()
    {
        auto readWriteMode = boost::interprocess::read_write;
        boost::interprocess::shared_memory_object sharedMemoryObject(
                boost::interprocess::open_only,
                _objectSpaceName.c_str(),
                readWriteMode
            );

        sharedMemoryObject.truncate(sizeof(BoundingSharedState));
        boost::interprocess::mapped_region mappedRegion(sharedMemoryObject, readWriteMode);
        auto mappedRegionAddress = mappedRegion.get_address();
        auto sharedState = static_cast<BoundingSharedState *>(mappedRegionAddress);

        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedState->mutex);
        if (sharedState->bufferEmpty)
            sharedState->read.wait(lock);

        auto content = AbstractBuffer::get();
        sharedState->write.notify_one();
        sharedState->bufferEmpty = true;

        return content;
    }

    void BoundedBuffer::put(const std::string & content)
    {
        auto readWriteMode = boost::interprocess::read_write;
        boost::interprocess::shared_memory_object sharedMemoryObject(
                boost::interprocess::open_only,
                _objectSpaceName.c_str(),
                readWriteMode
            );

        sharedMemoryObject.truncate(sizeof(BoundingSharedState));
        boost::interprocess::mapped_region mappedRegion(sharedMemoryObject, readWriteMode);
        auto mappedRegionAddress = mappedRegion.get_address();
        auto sharedState = static_cast<BoundingSharedState *>(mappedRegionAddress);

        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedState->mutex);
        if (!sharedState->bufferEmpty)
            sharedState->write.wait(lock);

        AbstractBuffer::put(content);
        sharedState->bufferEmpty = false;
        sharedState->read.notify_one();
    }

    /**
     * Inner class
     */

    BoundedBuffer
        ::BoundingSharedState::BoundingSharedState()
            : bufferEmpty(true)
        {}

    void BoundedBuffer
        ::BoundingSharedState::create(const std::string & objectName)
        {
            auto readWriteMode = boost::interprocess::read_write;
            boost::interprocess::shared_memory_object sharedMemoryObject(
                    boost::interprocess::create_only,
                    objectName.c_str(),
                    readWriteMode
                );

            sharedMemoryObject.truncate(sizeof(BoundingSharedState));
            boost::interprocess::mapped_region mappedRegion(sharedMemoryObject, readWriteMode);
            new(mappedRegion.get_address()) BoundingSharedState;
        }

    void BoundedBuffer
        ::BoundingSharedState::destroy(const std::string & objectName)
        {
            boost::interprocess::shared_memory_object::remove(objectName.c_str());
            try {
                boost::interprocess::shared_memory_object::remove(objectName.c_str());
            } catch (boost::interprocess::interprocess_exception & exception) {
                BOOST_ASSERT(exception.get_error_code() == boost::interprocess::not_found_error);
            }
        }


} }
