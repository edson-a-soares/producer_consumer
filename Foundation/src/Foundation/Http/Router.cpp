#include "Poco/URI.h"
#include "Foundation/Http/Router.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Adapter/Http/DefaultErrorHandler.h"

namespace Foundation {
namespace Http {


    Poco::Net::HTTPRequestHandler * Router::createRequestHandler(const Poco::Net::HTTPServerRequest & request)
    {
        using namespace Poco::Net;

	    loadEndpoints();
	    auto factoryKey = endpointFactoryKey(request.getURI());

        try {
            if (factoryKey.empty())
                return errorHandler()
                    ->status(HTTPResponse::HTTP_NOT_FOUND)
                    .detail("This endpoint does not exist.")
                    .type(HTTPResponse::HTTP_REASON_NOT_FOUND)
                    .build();

            auto resourceFactory = getResourceFactoryRoutingTable()->createResourceFactory(factoryKey);
            return resourceFactory->createResource();

        } catch (Poco::Exception & exception) {
            return errorHandler()
                ->detail(exception.displayText())
                .status(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR)
                .type(HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR)
                .build();
        }
    }

    std::unique_ptr<ErrorHandlerBuilderInterface> Router::errorHandler()
    {
        return std::make_unique<DefaultErrorHandler::Builder>();
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
