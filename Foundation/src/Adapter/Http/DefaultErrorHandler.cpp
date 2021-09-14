#include "Adapter/Http/DefaultErrorHandler.h"
#include "Adapter/Http/DefaultErrorMessageParser.h"

namespace Foundation {
namespace Http {


    DefaultErrorHandler::DefaultErrorHandler()
        : _status(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR)
    {}

    void DefaultErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType("application/xml");
        response.setStatusAndReason(_status);
        auto errorMessage = DefaultErrorMessageParser().toXml(_type, std::to_string(_status), _detail);

        response.sendBuffer(errorMessage.data(), errorMessage.length());
    }

    DefaultErrorHandler
        ::Builder::Builder()
            : errorHandler(new DefaultErrorHandler())
        {}

    Poco::Net::HTTPRequestHandler * DefaultErrorHandler
        ::Builder::build()
        {
            return errorHandler;
        }

    DefaultErrorHandler::Builder & DefaultErrorHandler
        ::Builder::type(std::string type)
        {
            errorHandler->_type = type;
            return *this;
        }

    DefaultErrorHandler::Builder & DefaultErrorHandler
        ::Builder::detail(std::string detail)
        {
            errorHandler->_detail = detail;
            return *this;
        }

    DefaultErrorHandler::Builder & DefaultErrorHandler
        ::Builder::status(Poco::Net::HTTPResponse::HTTPStatus code)
        {
            errorHandler->_status = code;
            return *this;
        }


} }
