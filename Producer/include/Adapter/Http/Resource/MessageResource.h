#ifndef Producer_Http_Resource_MessageResource_INCLUDED
#define Producer_Http_Resource_MessageResource_INCLUDED

#include "Producer/MessageService.h"
#include "Foundation/Http/AbstractResource.h"

namespace Producer {
namespace Http {


    class MessageResource : public Foundation::Http::AbstractResource
    {
    public:
        MessageResource();
        void setMessageService(::Producer::MessageService service);

    protected:
        void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    private:
        ::Producer::MessageService _messageService;

    };


} }

#endif
