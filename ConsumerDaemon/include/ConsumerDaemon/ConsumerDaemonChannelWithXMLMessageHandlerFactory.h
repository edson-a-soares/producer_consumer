#ifndef ConsumerDaemon_ConsumerDaemonChannelWithXMLMessageHandlerFactory_INCLUDED
#define ConsumerDaemon_ConsumerDaemonChannelWithXMLMessageHandlerFactory_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusChannelHandlerFactoryInterface.h"

namespace ConsumerDaemon {


    class API ConsumerDaemonChannelWithXMLMessageHandlerFactory : public MessageBusChannelHandlerFactoryInterface {
    public:
        std::function<std::string (const std::string & message)> messageHandlerFunction() override;
        std::unique_ptr<Foundation::IPC::MessageBusChannelInterface> messageBusChannelInformation() override;

    };


}

#endif
