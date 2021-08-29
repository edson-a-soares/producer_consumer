#include "ConsumerDaemon/MessageBusAbstractFactory.h"
#include "ConsumerDaemon/MessageBusXMLMessageFactory.h"

namespace ConsumerDaemon {


    std::unique_ptr<MessageBusFactoryInterface> MessageBusAbstractFactory::create(int)
    {
        return std::make_unique<MessageBusXMLMessageFactory>();
    }


}
