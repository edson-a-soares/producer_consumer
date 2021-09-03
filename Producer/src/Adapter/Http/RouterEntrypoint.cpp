#include "Poco/ClassLibrary.h"
#include "Adapter/Http/RouterEntrypoint.h"
#include "Adapter/Http/Resource/Factory/ProducerFactoryRoutingTable.h"

namespace Producer {
namespace Http {


    void RouterEntrypoint::loadEndpoints()
    {
        addEndpoint("/message", "Producer::Http::MessageResource");
    }

    std::unique_ptr<Foundation::Http::ResourceFactoryRoutingTableInterface>
        RouterEntrypoint::getResourceFactoryRoutingTable()
    {
        return std::make_unique<Producer::Http::ProducerFactoryRoutingTable>();
    }


} }

// add support to Poco ApacheConnector
POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
    POCO_EXPORT_CLASS(Producer::Http::RouterEntrypoint)
POCO_END_MANIFEST
