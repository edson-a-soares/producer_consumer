#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusFactory.h"
#include "Foundation/IPC/ConsumerDefaultMessageBusInformation.h"

namespace Foundation {
namespace IPC {


    void ConsumerDaemon::startListening(
        std::unique_ptr<MessageBusInformationInterface> messageBusInformation,
        const std::function<std::string (const std::string & message)> & callback)
    {
        auto messageBus = MessageBusFactory::getMessageBus(std::move(messageBusInformation));
        DaemonLoop::instance().runWith([=]() {
            messageBus->readMessage(callback);
        });
    }

    bool ConsumerDaemon::isListening()
    {
        return DaemonLoop::instance().isRunning();
    }

    void ConsumerDaemon::stopListening()
    {
        DaemonLoop::instance().turnOff();
    }


} }
