#ifndef ConsumerDaemon_MessageBusXMLMessageFactory_INCLUDED
#define ConsumerDaemon_MessageBusXMLMessageFactory_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "ConsumerDaemon/MessageBusFactoryInterface.h"

namespace ConsumerDaemon {


    class API MessageBusXMLMessageFactory : public MessageBusFactoryInterface {
    public:
        std::function<std::string (const std::string & message)> messageHandlerFunction() override;
        std::unique_ptr<Foundation::IPC::MessageBusInformationInterface> messageBusInformation() override;

    };


}

#endif
