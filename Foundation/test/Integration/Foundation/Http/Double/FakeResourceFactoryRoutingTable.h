#ifndef Foundation_Http_Double_FakeResourceFactoryRoutingTable_INCLUDED
#define Foundation_Http_Double_FakeResourceFactoryRoutingTable_INCLUDED

#include <string>
#include "FakeResourceFactory.h"
#include "Foundation/Http/Double/FakeResourceFactory.h"
#include "Foundation/Http/Double/ExceptionResourceFactory.h"
#include "Foundation/Http/ResourceFactoryRoutingTableInterface.h"

namespace Foundation {
namespace Http {


    /**
     * It matches the resource factories with the endpoints added to the router.
     */
    class FakeResourceFactoryRoutingTable : public Foundation::Http::ResourceFactoryRoutingTableInterface
    {
    public:
    	~FakeResourceFactoryRoutingTable() override = default;
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) override;

    };


    inline std::unique_ptr<Foundation::Http::ResourceFactoryInterface> FakeResourceFactoryRoutingTable::createResourceFactory(const std::string & resourceName)
    {
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> resourceFactory = nullptr;

        if ( resourceName == "Resource::FakeResource" )
            resourceFactory = std::make_unique<Foundation::Http::FakeResourceFactory>();

        if ( resourceName == "Resource::ExceptionResource" )
            resourceFactory = std::make_unique<Foundation::Http::ExceptionResourceFactory>();

        return resourceFactory;
    }


} }

#endif
