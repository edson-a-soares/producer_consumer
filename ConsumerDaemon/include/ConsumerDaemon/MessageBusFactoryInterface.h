#ifndef ConsumerDaemon_MessageBusFactoryInterface_INCLUDED
#define ConsumerDaemon_MessageBusFactoryInterface_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusInformationInterface.h"

namespace ConsumerDaemon {


    class API MessageBusFactoryInterface {
    public:
        virtual std::function<std::string (const std::string & message)> messageHandlerFunction() = 0;
        virtual std::unique_ptr<Foundation::IPC::MessageBusInformationInterface> messageBusInformation() = 0;

    };


}

#endif
