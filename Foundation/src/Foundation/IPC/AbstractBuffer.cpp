#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "boost/assert.hpp"
#include "Poco/Exception.h"
#include "Foundation/IPC/String.h"
#include "boost/interprocess/errors.hpp"
#include "Foundation/IPC/StringVector.h"
#include "Foundation/IPC/AbstractBuffer.h"
#include "boost/interprocess/managed_shared_memory.hpp"

namespace Foundation {
namespace IPC {


    AbstractBuffer::AbstractBuffer(const std::string & memoryName)
        : _memorySpaceName(memoryName)
    {
        if (memoryName.empty())
            throw Poco::InvalidArgumentException(0);

        if (!AbstractBuffer::exists())
            throw Poco::FileNotFoundException("Memory space do not exists.");
    }

    AbstractBuffer::AbstractBuffer(const std::string & memoryName, unsigned int memorySize)
        : _memorySpaceName(memoryName)
    {
        if (memoryName.empty() || memorySize == 0)
            throw Poco::InvalidArgumentException(0);

        if (AbstractBuffer::exists())
            throw Poco::FileExistsException("Memory space already exists.");

        create(memoryName, memorySize);
    }

    AbstractBuffer & AbstractBuffer::operator=(AbstractBuffer && other) noexcept
    {
        if (this == &other)
            return *this;

        *this = other;
        return *this;
    }

    AbstractBuffer & AbstractBuffer::operator=(const AbstractBuffer & other)
    {
        if (this == &other)
            return *this;

        *this = other;
        return *this;
    }

    void AbstractBuffer::destroy()
    {
        boost::interprocess::shared_memory_object::remove(_memorySpaceName.c_str());
        BOOST_ASSERT(!AbstractBuffer::exists());
    }

    void AbstractBuffer::clear()
    {
        boost::interprocess::managed_shared_memory sharedSegment(
                boost::interprocess::open_only,
                _memorySpaceName.c_str()
            );

        auto typeSizePair = sharedSegment.find<StringVector>(INTERNAL_DATA_STRUCTURE_NAME);
        auto vector = typeSizePair.first;
        vector->clear();
    }

    bool AbstractBuffer::empty()
    {
        boost::interprocess::managed_shared_memory sharedSegment(
                boost::interprocess::open_only,
                _memorySpaceName.c_str()
            );

        auto typeSizePair = sharedSegment.find<StringVector>(INTERNAL_DATA_STRUCTURE_NAME);
        auto vector = typeSizePair.first;
        return vector->empty();
    }

    bool AbstractBuffer::exists()
    {
        auto found = false;
        try {
            boost::interprocess::managed_shared_memory sharedSegment(
                    boost::interprocess::open_only,
                    _memorySpaceName.c_str()
                );

            found = sharedSegment.check_sanity();

        } catch (boost::interprocess::interprocess_exception & exception) {
            BOOST_ASSERT(exception.get_error_code() == boost::interprocess::not_found_error);
        }

        return found;
    }

    std::string AbstractBuffer::get()
    {
        boost::interprocess::managed_shared_memory sharedSegment(
                boost::interprocess::open_only,
                _memorySpaceName.c_str()
            );

        std::string content;
        auto typeSizePair = sharedSegment.find<StringVector>(INTERNAL_DATA_STRUCTURE_NAME);
        auto vector = typeSizePair.first;
        if ( vector->empty() )
            return content;

        auto interprocessContent = vector->front();
        content.assign(interprocessContent.begin(), interprocessContent.end());

        vector->clear();
        BOOST_ASSERT(vector->empty());

        return content;
    }

    void AbstractBuffer::put(const std::string & content)
    {
        boost::interprocess::managed_shared_memory sharedSegment(
                boost::interprocess::open_only,
                _memorySpaceName.c_str()
            );

        CharacterAllocator charAllocator(sharedSegment.get_segment_manager());
        String interprocessContent(content.c_str(), charAllocator);

        auto typeSizePair = sharedSegment.find<StringVector>(INTERNAL_DATA_STRUCTURE_NAME);
        auto vector       = typeSizePair.first;

        vector->insert(vector->begin(), interprocessContent);
        BOOST_ASSERT(!vector->empty());
    }

    void AbstractBuffer::create(const std::string & memoryName, unsigned int memorySize)
    {
        try {
            boost::interprocess::managed_shared_memory sharedSegment(
                    boost::interprocess::create_only,
                    memoryName.c_str(),
                    memorySize                                          // Shared Memory Space size in bytes.
                );

            BOOST_ASSERT(sharedSegment.check_sanity());
            BOOST_ASSERT(sharedSegment.get_num_named_objects() == 0);

            /*
             * This vector is fully constructed in shared memory.
             * All pointers buffers are constructed in the same shared memory segment.
             * This vector can be safely accessed from other processes.
             */
            StringAllocator stringAllocator(sharedSegment.get_segment_manager());
            sharedSegment.construct<StringVector>(INTERNAL_DATA_STRUCTURE_NAME)(stringAllocator);

            BOOST_ASSERT(sharedSegment.get_num_named_objects() == 1);

        } catch (boost::interprocess::interprocess_exception & exception) {
            BOOST_ASSERT_MSG(
                    exception.get_error_code() != 18,                   // boost::interprocess_exception::library_error
                    "You need a bigger memory size."
                );

        } catch (std::exception & exception) {
            std::cout << exception.what() << std::endl;
        }
    }


} }
