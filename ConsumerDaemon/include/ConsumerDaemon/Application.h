#ifndef ConsumerDaemon_Application_INCLUDED
#define ConsumerDaemon_Application_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusChannelHandlerFactoryInterface.h"

namespace ConsumerDaemon {


    class API Application {
    public:
        static void run(int channelHandler = 0, bool keepAlive = true);
        static std::unique_ptr<MessageBusChannelHandlerFactoryInterface> createMessageBusChannelHandler(int option);

    };


}

#endif
