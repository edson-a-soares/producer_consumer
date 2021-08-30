#ifndef ConsumerDaemon_MessageBusChannelHandlerFactoryInterface_INCLUDED
#define ConsumerDaemon_MessageBusChannelHandlerFactoryInterface_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace ConsumerDaemon {


    class API MessageBusChannelHandlerFactoryInterface {
    public:
        virtual std::function<std::string (const std::string & message)> messageHandlerFunction() = 0;
        virtual std::unique_ptr<Foundation::IPC::MessageBusChannelInterface> messageBusChannelInformation() = 0;

    };


}

#endif
