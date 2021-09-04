#ifndef Consumer_Http_Resource_Factory_ConsumerDaemonResourceFactory_INCLUDED
#define Consumer_Http_Resource_Factory_ConsumerDaemonResourceFactory_INCLUDED

#include "Foundation/Http/ResourceFactoryInterface.h"

namespace Consumer {
namespace Http {


    class ConsumerDaemonResourceFactory : public Foundation::Http::ResourceFactoryInterface
    {
    public:
        ~ConsumerDaemonResourceFactory() override = default;
        Poco::Net::HTTPRequestHandler * createResource() override;

    };


} }

#endif
