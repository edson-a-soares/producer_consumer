#ifndef Producer_Http_Resource_Factory_ProducerFactoryRoutingTable_INCLUDED
#define Producer_Http_Resource_Factory_ProducerFactoryRoutingTable_INCLUDED

#include <string>
#include "Foundation/Http/ResourceFactoryInterface.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"

namespace Producer {
namespace Http {


    class ProducerFactoryRoutingTable : public Foundation::Http::ResourceFactoryRoutingTableInterface
    {
    public:
    	~ProducerFactoryRoutingTable() override = default;
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) override;

    };


} }

#endif
