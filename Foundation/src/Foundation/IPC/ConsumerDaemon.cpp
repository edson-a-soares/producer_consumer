#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/BufferChannel.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusController.h"

namespace Foundation {
namespace IPC {


    void ConsumerDaemon::startMonitoring(const std::function<std::string (const std::string & message)> & callback)
    {
        auto messageBus = MessageBusController::createMessageBus();
        DaemonLoop::instance().runWith([=]() {
            messageBus->readMessage(callback);
        });
    }

    bool ConsumerDaemon::isMonitoring()
    {
        return DaemonLoop::instance().isRunning();
    }

    void ConsumerDaemon::stopMonitoring()
    {
        DaemonLoop::instance().turnOff();
    }


} }
