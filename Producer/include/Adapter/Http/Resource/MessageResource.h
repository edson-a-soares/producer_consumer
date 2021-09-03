#ifndef Producer_Http_Resource_MessageResource_INCLUDED
#define Producer_Http_Resource_MessageResource_INCLUDED

#include "Foundation/Http/AbstractResource.h"

namespace Producer {
namespace Http {


    class MessageResource : public Foundation::Http::AbstractResource
    {
    public:
        MessageResource() = default;

    protected:
        void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


} }

#endif
