#ifndef Foundation_Http_Double_ExceptionResourceFactory_INCLUDED
#define Foundation_Http_Double_ExceptionResourceFactory_INCLUDED

#include "Foundation/Http/ResourceFactoryInterface.h"
#include "Foundation/Http/Double/FakeResource.h"

namespace Foundation {
namespace Http {


    class ExceptionResourceFactory : public Foundation::Http::ResourceFactoryInterface
    {
    public:
        ~ExceptionResourceFactory() override = default;
        Poco::Net::HTTPRequestHandler * createResource() override;

    };


    inline Poco::Net::HTTPRequestHandler * ExceptionResourceFactory::createResource()
    {
        throw Poco::NullPointerException("NullPointerException");
        return nullptr;
    }


} }

#endif
