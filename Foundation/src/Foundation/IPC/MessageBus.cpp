#include "Poco/Exception.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/IPC/BoundedBuffer.h"

#include <iostream>

namespace Foundation {
namespace IPC {


    MessageBus::MessageBus(std::unique_ptr<BoundedBuffer> input, std::unique_ptr<BoundedBuffer> output)
        : automaticChannelsManagement(true),
          inputChannel(std::move(input)),
          outputChannel(std::move(output))
    {}

    MessageBus::~MessageBus() {
        poco_debugger_msg("MessageBus::~MessageBus()");
        if (automaticChannelsManagement)
            destroyChannels();
    }

    std::string MessageBus::readResponse()
    {
        return outputChannel->get();
    }

    void MessageBus::sendMessage(const std::string & content)
    {
        try {
            inputChannel->put(content);

        } catch (Poco::Exception &) {
            std::cout << "MessageBus::sendMessage(const std::string &)" << std::endl;
            //throw;
        } catch (...) {
            std::cout << "MessageBus::sendMessage(const std::string &)" << std::endl;
        }
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

    void MessageBus::disableInternalChannelsLifecycleManagement()
    {
        automaticChannelsManagement = false;
    }


    /**
     * MessageBus::Factory
     */
    std::shared_ptr<MessageBus> MessageBus
        ::Factory::create(std::unique_ptr<MessageBusChannelInterface> information)
        {
            auto messageBus = construct(std::move(information));
            return messageBus;
        }

    std::shared_ptr<MessageBus> MessageBus
        ::Factory::createClient(std::unique_ptr<MessageBusChannelInterface> information)
        {
            auto messageBus = construct(std::move(information));
            messageBus->disableInternalChannelsLifecycleManagement();
            return messageBus;
        }

    std::shared_ptr<MessageBus> MessageBus
        ::Factory::construct(std::unique_ptr<MessageBusChannelInterface> channel) {
            std::unique_ptr<BoundedBuffer> input  = nullptr;
            std::unique_ptr<BoundedBuffer> output = nullptr;

            try {
                input  = std::make_unique<BoundedBuffer>(channel->inputName());
                output = std::make_unique<BoundedBuffer>(channel->outputName());

            } catch (Poco::FileNotFoundException &) {
                input  = std::make_unique<BoundedBuffer>(channel->inputName(), channel->length());
                output = std::make_unique<BoundedBuffer>(channel->outputName(), channel->length());

            }

            return std::shared_ptr<MessageBus>(new MessageBus(std::move(input), std::move(output)));
        }


} }
