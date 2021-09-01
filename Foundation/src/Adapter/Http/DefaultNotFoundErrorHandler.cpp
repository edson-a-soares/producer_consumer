#include "Adapter/Http/DefaultErrorMessageParser.h"
#include "Adapter/Http/DefaultNotFoundErrorHandler.h"

namespace Http {


	void DefaultNotFoundErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
	{
        response.setContentType("application/xml");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);

        auto messageParser = DefaultErrorMessageParser();
        auto errorMessage = messageParser.toXml(
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND,
            std::to_string(Poco::Net::HTTPResponse::HTTP_NOT_FOUND),
            "Endpoint does not exist."
        );

        response.sendBuffer(errorMessage.data(), errorMessage.length());
	}


}
