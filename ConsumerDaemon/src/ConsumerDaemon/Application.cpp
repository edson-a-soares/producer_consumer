#include <csignal>
#include "ConsumerDaemon/Application.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "ConsumerDaemon/MainChannelWithXMLMessageHandlerFactory.h"
#include "ConsumerDaemon/DefaultChannelWithXMLMessageHandlerFactory.h"

namespace ConsumerDaemon {


    void _signalHandler(int signal){
        if (signal != SIGTERM)
            return;

        Foundation::IPC::ConsumerDaemon::stopListening();
    }

    void Application::runOn(ChannelOption option, bool keepAlive)
    {
        auto abstractFactory = createMessageBusChannelHandler(option);

        Foundation::IPC::ConsumerDaemon::startListening(
            abstractFactory->messageBusChannelInformation(),
            abstractFactory->messageHandlerFunction()
        );

        // It keeps the process alive even while waiting for data to process.
        if (keepAlive) {
            signal(SIGTERM, _signalHandler);
            while (Foundation::IPC::ConsumerDaemon::isListening());
        }
    }

    std::unique_ptr<MessageBusChannelHandlerFactoryInterface> Application::createMessageBusChannelHandler(ChannelOption option)
    {
        std::unique_ptr<MessageBusChannelHandlerFactoryInterface> abstractFactory = nullptr;

        switch (option) {
            case MAIN_CHANNEL:
                abstractFactory = std::make_unique<MainChannelWithXMLMessageHandlerFactory>();
                break;

            default:
                abstractFactory = std::make_unique<DefaultChannelWithXMLMessageHandlerFactory>();
        }

        return abstractFactory;
    }


}
