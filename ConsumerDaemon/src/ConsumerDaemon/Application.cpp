#include "ConsumerDaemon/Application.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "ConsumerDaemon/MessageBusAbstractFactory.h"

namespace ConsumerDaemon {


    void Application::run(int option, bool keepAlive)
    {
        auto abstractFactory = MessageBusAbstractFactory::create(option);

        Foundation::IPC::ConsumerDaemon::startListening(
            abstractFactory->messageBusInformation(),
            abstractFactory->messageHandlerFunction()
        );

        // It keeps the process alive even while waiting for data to process.
        if (keepAlive)
            while(Foundation::IPC::ConsumerDaemon::isListening());
    }


}
