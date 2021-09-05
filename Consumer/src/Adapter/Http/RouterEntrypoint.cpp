#include "Poco/ClassLibrary.h"
#include "Adapter/Http/RouterEntrypoint.h"
#include "Adapter/Http/Resource/Factory/ConsumerFactoryRoutingTable.h"

namespace Consumer {
namespace Http {


    void RouterEntrypoint::loadEndpoints()
    {
        commonPathPrefix("/consumer");
        addEndpoint("/daemon_loop", "Consumer::Http::ConsumerDaemonResource");
    }

    std::unique_ptr<Foundation::Http::ResourceFactoryRoutingTableInterface>
        RouterEntrypoint::getResourceFactoryRoutingTable()
    {
        return std::make_unique<Consumer::Http::ConsumerFactoryRoutingTable>();
    }


} }

// add support to Poco ApacheConnector
POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
    POCO_EXPORT_CLASS(Consumer::Http::RouterEntrypoint)
POCO_END_MANIFEST
