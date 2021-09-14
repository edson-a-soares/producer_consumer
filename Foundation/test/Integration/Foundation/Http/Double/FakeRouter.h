#ifndef Foundation_Http_Double_FakeRouter_INCLUDED
#define Foundation_Http_Double_FakeRouter_INCLUDED

#include "Foundation/Http/Router.h"
#include "Foundation/Http/Double/EscapedErrorHandler.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"
#include "Foundation/Http/Double/FakeResourceFactoryRoutingTable.h"

namespace Foundation {
namespace Http {


    class FakeRouter : public Foundation::Http::Router
    {
    public:
        void loadEndpoints() override;
        std::unique_ptr<ErrorHandlerBuilderInterface> errorHandler() override;
        std::unique_ptr<Foundation::Http::ResourceFactoryRoutingTableInterface> getResourceFactoryRoutingTable() override;

    };


    inline void FakeRouter::loadEndpoints()
    {
        addEndpoint("/test_endpoint",           "Resource::FakeResource");
        addEndpoint("/test_endpoint_exception", "Resource::ExceptionResource");
    }

    std::unique_ptr<ErrorHandlerBuilderInterface> FakeRouter::errorHandler()
    {
        return std::make_unique<EscapedErrorHandler::Builder>();
    }

    inline std::unique_ptr<Foundation::Http::ResourceFactoryRoutingTableInterface> FakeRouter::getResourceFactoryRoutingTable()
    {
        return std::make_unique<Foundation::Http::FakeResourceFactoryRoutingTable>();
    }


} }

#endif
