#ifndef ConsumerDaemon_DefaultChannelWithXMLMessageHandlerFactory_INCLUDED
#define ConsumerDaemon_DefaultChannelWithXMLMessageHandlerFactory_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusChannelHandlerFactoryInterface.h"

namespace ConsumerDaemon {


    class API DefaultChannelWithXMLMessageHandlerFactory : public MessageBusChannelHandlerFactoryInterface {
    public:
        std::function<std::string (const std::string & message)> messageHandlerFunction() override;
        std::unique_ptr<Foundation::IPC::MessageBusChannelInterface> messageBusChannelInformation() override;

    };


}

#endif
