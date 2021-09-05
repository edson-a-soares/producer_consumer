#ifndef Foundation_Http_Router_INCLUDED
#define Foundation_Http_Router_INCLUDED

#include <map>
#include <memory>
#include <string>
#include "Foundation/Foundation.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"

namespace Foundation {
namespace Http {


    class API Router : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        ~Router() override = default;
        Poco::Net::HTTPRequestHandler * createRequestHandler (const Poco::Net::HTTPServerRequest &) final;

    protected:
        virtual void loadEndpoints() = 0;
        void commonPathPrefix(const std::string & path);
        virtual Poco::Net::HTTPRequestHandler * notFoundErrorHandler();
        void addEndpoint(const std::string & path, const std::string & resourceFactoryName);
        virtual std::unique_ptr<ResourceFactoryRoutingTableInterface> getResourceFactoryRoutingTable() = 0;

    private:
        std::string _pathPrefix;
        std::map<std::string, std::string> routingTable = {};

        std::string endpointFactoryKey(const std::string & path);

    };


} }

#endif
