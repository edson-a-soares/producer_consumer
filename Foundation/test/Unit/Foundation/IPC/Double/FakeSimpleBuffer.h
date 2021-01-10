#ifndef Double_IPC_FakeSimpleBuffer_INCLUDED
#define Double_IPC_FakeSimpleBuffer_INCLUDED

#include <string>
#include "Foundation/IPC/AbstractBuffer.h"

namespace Double {


    class FakeSimpleBuffer : public Foundation::IPC::AbstractBuffer {
    public:
        FakeSimpleBuffer() = delete;
        ~FakeSimpleBuffer() override = default;
        explicit FakeSimpleBuffer(const std::string & memoryName);
        FakeSimpleBuffer(const std::string & memoryName, unsigned int memorySize);

    };


    inline FakeSimpleBuffer::FakeSimpleBuffer(const std::string & memoryName)
        : AbstractBuffer(memoryName)
    {}

    inline FakeSimpleBuffer::FakeSimpleBuffer(const std::string & memoryName, unsigned int memorySize)
        : AbstractBuffer(memoryName, memorySize)
    {}


}

#endif
