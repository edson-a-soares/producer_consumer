#ifndef Consumer_Http_Resource_Factory_ConsumerFactoryRoutingTable_INCLUDED
#define Consumer_Http_Resource_Factory_ConsumerFactoryRoutingTable_INCLUDED

#include <string>
#include "Foundation/Http/ResourceFactoryInterface.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"

namespace Consumer {
namespace Http {


    class ConsumerFactoryRoutingTable : public Foundation::Http::ResourceFactoryRoutingTableInterface
    {
    public:
    	~ConsumerFactoryRoutingTable() override = default;
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) override;

    };


} }

#endif
