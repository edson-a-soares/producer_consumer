#ifndef Consumer_Http_Resource_ConsumerDaemonResource_INCLUDED
#define Consumer_Http_Resource_ConsumerDaemonResource_INCLUDED

#include "Foundation/Http/AbstractResource.h"

namespace Consumer {
namespace Http {


    class ConsumerDaemonResource : public Foundation::Http::AbstractResource
    {
    public:
        ConsumerDaemonResource() = default;

    protected:
        void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


} }

#endif
