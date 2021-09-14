#ifndef Foundation_Http_Double_EscapedErrorHandler_INCLUDED
#define Foundation_Http_Double_EscapedErrorHandler_INCLUDED

#include "Poco/URI.h"
#include "Poco/String.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Foundation/Http/ErrorHandlerBuilderInterface.h"
#include "Foundation/Http/Double/EscapedErrorMessageParser.h"

namespace Foundation {
namespace Http {


    class EscapedErrorHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        EscapedErrorHandler();
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

        class Builder : public ErrorHandlerBuilderInterface
        {
        public:
            Builder();
            ~Builder() = default;
            Builder & type(std::string) final;
            Builder & detail(std::string) final;
            Poco::Net::HTTPRequestHandler * build() final;
            Builder & status(Poco::Net::HTTPResponse::HTTPStatus) final;

        private:
            EscapedErrorHandler * errorHandler;

        };

    private:
        std::string _type;
        std::string _detail;
        Poco::Net::HTTPResponse::HTTPStatus _status;

        friend Builder;
    };


    EscapedErrorHandler::EscapedErrorHandler()
        : _status(Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR)
    {}

    void EscapedErrorHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType("application/xml");
        response.setStatusAndReason(_status);
        auto errorMessage = EscapedErrorMessageParser().toXml(
            _type,
            std::to_string(_status),
            Poco::trim(_detail.substr(_detail.find(':')+1))
        );

        response.sendBuffer(errorMessage.data(), errorMessage.length());
    }

    EscapedErrorHandler
        ::Builder::Builder()
            : errorHandler(new EscapedErrorHandler())
        {}

    Poco::Net::HTTPRequestHandler * EscapedErrorHandler
        ::Builder::build()
        {
            return errorHandler;
        }

    EscapedErrorHandler::Builder & EscapedErrorHandler
        ::Builder::type(std::string type)
        {
            errorHandler->_type = type;
            return *this;
        }

    EscapedErrorHandler::Builder & EscapedErrorHandler
        ::Builder::detail(std::string detail)
        {
            errorHandler->_detail = detail;
            return *this;
        }

    EscapedErrorHandler::Builder & EscapedErrorHandler
        ::Builder::status(Poco::Net::HTTPResponse::HTTPStatus code)
        {
            errorHandler->_status = code;
            return *this;
        }


} }

#endif
