#ifndef Foundation_IPC_BoundedBuffer_INCLUDED
#define Foundation_IPC_BoundedBuffer_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/AbstractBuffer.h"
#include "boost/interprocess/sync/interprocess_mutex.hpp"
#include "boost/interprocess/sync/interprocess_condition.hpp"

namespace Foundation {
namespace IPC {


    class API BoundedBuffer : public AbstractBuffer {
    public:
        BoundedBuffer() = delete;
        ~BoundedBuffer() override = default;
        explicit BoundedBuffer(const std::string & memoryName);
        BoundedBuffer(const std::string & memoryName, unsigned int memorySize);
        BoundedBuffer(BoundedBuffer &&) noexcept = default;         // Move constructor
        BoundedBuffer(BoundedBuffer const &) = default;             // Copy constructor
        BoundedBuffer & operator=(BoundedBuffer &&) noexcept;       // Move assign
        BoundedBuffer & operator=(BoundedBuffer const &);           // Copy assign
        void clear() override;
        void destroy() override;
        std::string get() override;
        void put(const std::string & content) override;

    private:
        class BoundingSharedState {
        private:
            BoundingSharedState();

            bool bufferEmpty;

            // Mutex to control reading and writing to the buffer.
            boost::interprocess::interprocess_mutex mutex;

            // Condition to wait, write, or read body to the buffer according to its status.
            boost::interprocess::interprocess_condition  read;
            boost::interprocess::interprocess_condition  write;

            static void create(const std::string & objectName);
            static void destroy(const std::string & objectName);

            friend BoundedBuffer;
        };

        const std::string _objectSpaceName;
        static constexpr const char * SHARED_OBJECT_SUFFIX = "__OBJECT";

    };


} }

#endif
