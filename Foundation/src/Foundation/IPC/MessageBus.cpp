#include "Foundation/IPC/MessageBus.h"
#include "Foundation/IPC/BoundedBuffer.h"

namespace Foundation {
namespace IPC {


    MessageBus::MessageBus(std::unique_ptr<BoundedBuffer> input, std::unique_ptr<BoundedBuffer> output)
        : inputChannel(std::move(input)),
          outputChannel(std::move(output)),
          automaticChannelsManagement(true)
    {}

    MessageBus::~MessageBus() {
        if (automaticChannelsManagement)
            destroyChannels();
    }

    std::string MessageBus::readResponse()
    {
        return outputChannel->get();
    }

    void MessageBus::sendMessage(const std::string & content)
    {
        inputChannel->put(content);
    }

    void MessageBus::readMessage(const std::function<std::string (const std::string & message)> & messageHandler) const
    {
        if (inputChannel->empty())
            return;

        outputChannel->put(messageHandler(inputChannel->get()));
    }

    void MessageBus::sendMessage(const std::string & content, const std::function<void (const std::string &)> & responseHandler)
    {
        inputChannel->put(content);
        responseHandler(outputChannel->get());
    }

    void MessageBus::destroyChannels() {
        if (inputChannel->exists()) {
            inputChannel->clear();
            inputChannel->destroy();
        }

        if (outputChannel->exists()) {
            outputChannel->clear();
            outputChannel->destroy();
        }
    }

    void MessageBus::disableChannelsManagement()
    {
        automaticChannelsManagement = false;
    }


} }
