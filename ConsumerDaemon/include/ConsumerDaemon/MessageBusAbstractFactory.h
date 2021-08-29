#ifndef ConsumerDaemon_MessageBusAbstractFactory_INCLUDED
#define ConsumerDaemon_MessageBusAbstractFactory_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusFactoryInterface.h"

namespace ConsumerDaemon {


    class API MessageBusAbstractFactory {
    public:
        static std::unique_ptr<MessageBusFactoryInterface> create(int);

    };


}

#endif
