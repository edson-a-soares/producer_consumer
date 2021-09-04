#include "Adapter/Http/Resource/Factory/ConsumerDaemonResourceFactory.h"
#include "Adapter/Http/Resource/Factory/ConsumerFactoryRoutingTable.h"

namespace Consumer {
namespace Http {


	std::unique_ptr<Foundation::Http::ResourceFactoryInterface> ConsumerFactoryRoutingTable::createResourceFactory(const std::string & resourceName)
	{
		std::unique_ptr<Foundation::Http::ResourceFactoryInterface> resourceFactory = nullptr;

		if ( resourceName == "Consumer::Http::ConsumerDaemonResource" )
			resourceFactory = std::make_unique<ConsumerDaemonResourceFactory>();

		return resourceFactory;
	}


} }
