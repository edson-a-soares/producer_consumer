#include "Adapter/Http/Resource/ConsumerDaemonResource.h"
#include "Adapter/Http/Resource/Factory/ConsumerDaemonResourceFactory.h"

namespace Consumer {
namespace Http {


    Poco::Net::HTTPRequestHandler * ConsumerDaemonResourceFactory::createResource()
    {
        return new ConsumerDaemonResource();
    }


} }
