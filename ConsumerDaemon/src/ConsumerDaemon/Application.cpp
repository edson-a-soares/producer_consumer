#include "ConsumerDaemon/Application.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "ConsumerDaemon/DefaultChannelWithXMLMessageHandlerFactory.h"
#include "ConsumerDaemon/ConsumerDaemonChannelWithXMLMessageHandlerFactory.h"

namespace ConsumerDaemon {


    void Application::run(int channelHandler, bool keepAlive)
    {
        auto abstractFactory = createMessageBusChannelHandler(channelHandler);

        Foundation::IPC::ConsumerDaemon::startListening(
            abstractFactory->messageBusChannelInformation(),
            abstractFactory->messageHandlerFunction()
        );

        // It keeps the process alive even while waiting for data to process.
        if (keepAlive)
            while(Foundation::IPC::ConsumerDaemon::isListening());
    }

    std::unique_ptr<MessageBusChannelHandlerFactoryInterface> Application::createMessageBusChannelHandler(int option)
    {
        std::unique_ptr<MessageBusChannelHandlerFactoryInterface> abstractFactory = nullptr;

        switch (option) {
            case 1:
                abstractFactory = std::make_unique<ConsumerDaemonChannelWithXMLMessageHandlerFactory>();
            break;

            default:
                abstractFactory = std::make_unique<DefaultChannelWithXMLMessageHandlerFactory>();
        }

        return abstractFactory;
    }


}
