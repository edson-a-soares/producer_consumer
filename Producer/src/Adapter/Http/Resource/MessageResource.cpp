#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Adapter/Http/Resource/MessageResource.h"

namespace Producer {
namespace Http {


    MessageResource::MessageResource()
        : _messageService()
    {}

    void MessageResource::handle_post(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Poco::Net;

        std::string requestBody;
        std::string responseXMLMessage;
        std::istream & inputStream = request.stream();
        Poco::StreamCopier::copyToString(inputStream, requestBody);

        if (requestBody.empty())
            throw Poco::InvalidArgumentException("Bad Request",
                Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
            );

        try {
            auto responseMessage = _messageService.exchange(requestBody);
            responseXMLMessage = responseMessage->toXml();

        } catch (Poco::InvalidArgumentException & exception) {
            throw Poco::Exception(exception.displayText(),
                Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
            );

        } catch (Poco::Exception & exception) {
            throw Poco::Exception(exception.displayText(),
                Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR,
                Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR
            );
        }

        response.sendBuffer(responseXMLMessage.data(), responseXMLMessage.length());
    }

    void MessageResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "POST, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }

    void MessageResource::setMessageService(::Producer::MessageService service)
    {
        _messageService = service;
    }


} }
