#ifndef Foundation_Http_Double_EscapedNotFoundErrorHandler_INCLUDED
#define Foundation_Http_Double_EscapedNotFoundErrorHandler_INCLUDED

#include "Poco/URI.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Foundation/Http/Double/EscapedErrorMessageParser.h"

namespace Foundation {
namespace Http {


    class EscapedNotFoundErrorHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


    void EscapedNotFoundErrorHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType("application/xml");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);

        auto errorParser = EscapedErrorMessageParser();
        auto errorMessage = errorParser.toXml(
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND,
            std::to_string(Poco::Net::HTTPResponse::HTTP_NOT_FOUND),
            "Endpoint does not exist."
        );

        response.sendBuffer(errorMessage.data(), errorMessage.length());
    }


} }

#endif
