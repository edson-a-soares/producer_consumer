#include "Adapter/Http/Resource/MessageResource.h"
#include "Adapter/Http/Resource/Factory/MessageResourceFactory.h"

namespace Producer {
namespace Http {


    Poco::Net::HTTPRequestHandler * MessageResourceFactory::createResource()
    {
        return new MessageResource();
    }


} }
