#include "Producer/MessageService.h"
#include "Foundation/IPC/MessageBus.h"
#include "Adapter/Http/Resource/MessageResource.h"
#include "Foundation/IPC/DefaultMessageBusChannel.h"
#include "Adapter/Http/Resource/Factory/MessageResourceFactory.h"

namespace Producer {
namespace Http {


    Poco::Net::HTTPRequestHandler * MessageResourceFactory::createResource()
    {
        using namespace Foundation::IPC;

        auto resource = new MessageResource();
        auto service  = MessageService (MessageBus::Factory::createClient(std::make_unique<DefaultMessageBusChannel>()));
        resource->setMessageService(service);

        return resource;
    }


} }
