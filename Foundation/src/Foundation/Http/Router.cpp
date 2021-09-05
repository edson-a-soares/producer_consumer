#include "Poco/URI.h"
#include "Foundation/Http/Router.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Adapter/Http/DefaultNotFoundErrorHandler.h"

namespace Foundation {
namespace Http {


    Poco::Net::HTTPRequestHandler * Router::createRequestHandler(const Poco::Net::HTTPServerRequest & request)
    {
	    loadEndpoints();
	    auto factoryKey = endpointFactoryKey(request.getURI());

	    if (factoryKey.empty()) {
            auto errorHandler = notFoundErrorHandler();
            if (errorHandler == nullptr)
                errorHandler = new ::Http::DefaultNotFoundErrorHandler();

            return errorHandler;
        }

	    auto factory = getResourceFactoryRoutingTable()->createResourceFactory(factoryKey);
	    return factory->createResource();
    }

    Poco::Net::HTTPRequestHandler * Router::notFoundErrorHandler()
    {
        return nullptr;
    }

    std::string Router::endpointFactoryKey(const std::string & path)
    {
	    std::string route;
	    Poco::URI uri = Poco::URI(path);

	    if ( routingTable.find(uri.getPath()) != routingTable.end() ) {
		    auto routeIndex = routingTable.find(uri.getPath());
		    route = routeIndex->second;
	    }

	    return route;
    }

    void Router::commonPathPrefix(const std::string & path)
    {
        _pathPrefix = path;
    }

    void Router::addEndpoint(const std::string & path, const std::string & resourceFactoryName)
    {
        auto key = _pathPrefix.empty() ? path : _pathPrefix + path;
        routingTable[key] = resourceFactoryName;
    }


} }
