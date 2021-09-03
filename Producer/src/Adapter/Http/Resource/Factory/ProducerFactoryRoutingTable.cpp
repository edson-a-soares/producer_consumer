#include "Adapter/Http/Resource/Factory/MessageResourceFactory.h"
#include "Adapter/Http/Resource/Factory/ProducerFactoryRoutingTable.h"

namespace Producer {
namespace Http {


	std::unique_ptr<Foundation::Http::ResourceFactoryInterface> ProducerFactoryRoutingTable::createResourceFactory(const std::string & resourceName)
	{
		std::unique_ptr<Foundation::Http::ResourceFactoryInterface> resourceFactory = nullptr;

		if ( resourceName == "Producer::Http::MessageResource" )
			resourceFactory = std::make_unique<MessageResourceFactory>();

		return resourceFactory;
	}


} }
