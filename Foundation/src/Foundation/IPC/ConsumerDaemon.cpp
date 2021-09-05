#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/DefaultMessageBusChannel.h"

namespace Foundation {
namespace IPC {


    void ConsumerDaemon::startListening(
        std::unique_ptr<MessageBusChannelInterface> messageBusInformation,
        const std::function<std::string (const std::string & message)> & callback,
        bool cleanOnStop)
    {
        auto messageBus = MessageBus::Factory::create(std::move(messageBusInformation));
        DaemonLoop::instance().runWith([=]() {
            messageBus->readMessage(callback);
        });

        if (cleanOnStop)
            messageBus->destroyChannels();
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
