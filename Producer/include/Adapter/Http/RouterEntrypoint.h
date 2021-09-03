#ifndef Producer_Http_RouterEntrypoint_INCLUDED
#define Producer_Http_RouterEntrypoint_INCLUDED

#include "Foundation/Foundation.h"
#include "Foundation/Http/Router.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"

namespace Producer {
namespace Http {


    class API RouterEntrypoint : public Foundation::Http::Router
    {
    public:
        ~RouterEntrypoint() override = default;
        void loadEndpoints() override;
        std::unique_ptr<Foundation::Http::ResourceFactoryRoutingTableInterface> getResourceFactoryRoutingTable() override;

    };


} }

#endif
