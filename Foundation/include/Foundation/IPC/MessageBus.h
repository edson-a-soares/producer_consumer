#ifndef Foundation_IPC_MessageBus_INCLUDED
#define Foundation_IPC_MessageBus_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/BoundedBuffer.h"

namespace Foundation {
namespace IPC {


    class API MessageBus {
    public:
        MessageBus() = delete;
        ~MessageBus() = default;
        MessageBus(MessageBus &) = delete;
        MessageBus(MessageBus &&) noexcept = default;
        MessageBus(std::unique_ptr<BoundedBuffer> inputChannel, std::unique_ptr<BoundedBuffer> outputChannel);

        // void * operator new (size_t) = delete;

        std::string readResponse();
        void sendMessage(const std::string & content);
        void readMessage(const std::function<std::string (const std::string & message)> & messageHandler) const;
        void sendMessage(const std::string & message, const std::function<void (const std::string & response)> & responseHandler);

    private:
        std::unique_ptr<BoundedBuffer> inputChannel;
        std::unique_ptr<BoundedBuffer> outputChannel;

    };


} }

#endif
