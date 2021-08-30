#ifndef ConsumerDaemon_MainChannelWithXMLMessageHandlerFactory_INCLUDED
#define ConsumerDaemon_MainChannelWithXMLMessageHandlerFactory_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusChannelHandlerFactoryInterface.h"

namespace ConsumerDaemon {


    class API MainChannelWithXMLMessageHandlerFactory : public MessageBusChannelHandlerFactoryInterface {
    public:
        std::function<std::string (const std::string & message)> messageHandlerFunction() override;
        std::unique_ptr<Foundation::IPC::MessageBusChannelInterface> messageBusChannelInformation() override;

    };


}

#endif
