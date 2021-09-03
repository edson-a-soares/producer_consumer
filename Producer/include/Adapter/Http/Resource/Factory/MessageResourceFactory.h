#ifndef Producer_Http_Resource_Factory_MessageResourceFactory_INCLUDED
#define Producer_Http_Resource_Factory_MessageResourceFactory_INCLUDED

#include "Foundation/Http/ResourceFactoryInterface.h"

namespace Producer {
namespace Http {


    class MessageResourceFactory : public Foundation::Http::ResourceFactoryInterface
    {
    public:
        ~MessageResourceFactory() override = default;
        Poco::Net::HTTPRequestHandler * createResource() override;

    };


} }

#endif
