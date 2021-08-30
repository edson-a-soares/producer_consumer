#ifndef ConsumerDaemon_Application_INCLUDED
#define ConsumerDaemon_Application_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusChannelHandlerFactoryInterface.h"

namespace ConsumerDaemon {


    class API Application {
    public:
        enum ChannelOption {
            DEFAULT_CHANNEL = 0,
            MAIN_CHANNEL
        };

        static void runOn(ChannelOption option = DEFAULT_CHANNEL, bool keepAlive = true);
        static std::unique_ptr<MessageBusChannelHandlerFactoryInterface>
            createMessageBusChannelHandler(ChannelOption option = DEFAULT_CHANNEL);

    };


}

#endif
