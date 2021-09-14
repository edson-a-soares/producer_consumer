#ifndef Http_DefaultErrorHandlerBuilder_INCLUDED
#define Http_DefaultErrorHandlerBuilder_INCLUDED

#include "Poco/Exception.h"
#include "Foundation/Foundation.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Foundation/Http/ErrorHandlerBuilderInterface.h"

namespace Foundation {
namespace Http {


    class API DefaultErrorHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        DefaultErrorHandler();
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
            DefaultErrorHandler * errorHandler;

        };

    private:
        std::string _type;
        std::string _detail;
        Poco::Net::HTTPResponse::HTTPStatus _status;

        friend Builder;
    };


} }

#endif
