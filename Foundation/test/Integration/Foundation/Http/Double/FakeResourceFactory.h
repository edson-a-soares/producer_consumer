#ifndef Foundation_Http_Double_FakeResourceFactory_INCLUDED
#define Foundation_Http_Double_FakeResourceFactory_INCLUDED

#include "Foundation/Http/ResourceFactoryInterface.h"
#include "Foundation/Http/Double/FakeResource.h"

namespace Foundation {
namespace Http {


    /**
     * It just creates a resource and does the dependency injection work, if needed.
     */
    class FakeResourceFactory : public Foundation::Http::ResourceFactoryInterface
    {
    public:
        ~FakeResourceFactory() override = default;
        Poco::Net::HTTPRequestHandler * createResource() override;

    };


    inline Poco::Net::HTTPRequestHandler * FakeResourceFactory::createResource()
    {
        return new Foundation::Http::FakeResource();
    }


} }

#endif
