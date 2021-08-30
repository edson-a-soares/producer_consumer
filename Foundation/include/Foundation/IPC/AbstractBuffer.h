#ifndef Foundation_IPC_AbstractBuffer_INCLUDED
#define Foundation_IPC_AbstractBuffer_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/BufferInterface.h"

namespace Foundation {
namespace IPC {


    class API AbstractBuffer : public BufferInterface {
    public:
        AbstractBuffer() = delete;
        ~AbstractBuffer() override;
        AbstractBuffer(AbstractBuffer &&) noexcept = default;   // Move constructor
        AbstractBuffer(AbstractBuffer const &) = default;       // Copy constructor
        AbstractBuffer & operator=(AbstractBuffer &&) noexcept; // Move assign
        AbstractBuffer & operator=(AbstractBuffer const &);     // Copy assign
        void clear() override;
        bool empty() override;
        bool exists() override;
        void destroy() override;
        std::string get() override;
        void put(const std::string & content) override;

    protected:
        explicit AbstractBuffer(const std::string & memoryName);
        AbstractBuffer(const std::string & memoryName, unsigned int memorySize);

    private:
        const std::string _memorySpaceName;
        static constexpr const char * INTERNAL_DATA_STRUCTURE_NAME = "__BUFFER_DATA_STRUCTURE__";

        static void create(const std::string & memoryName, unsigned int memorySize);

    };


} }

#endif
