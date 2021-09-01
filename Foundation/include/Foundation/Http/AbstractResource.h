#ifndef Foundation_Http_AbstractResource_INCLUDED
#define Foundation_Http_AbstractResource_INCLUDED

#include <memory>
#include "Foundation/Foundation.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Foundation/Http/ErrorMessageParserInterface.h"

namespace Foundation {
namespace Http {


    class API AbstractResource : public Poco::Net::HTTPRequestHandler
    {
    public:
        ~AbstractResource() override = default;
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    protected:
        virtual std::unique_ptr<ErrorMessageParserInterface> createErrorMessageParser();
        virtual void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_put(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_patch(  Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_delete( Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

    private:
        static void dispatch(Poco::Net::HTTPServerResponse &);
        void dispatchError(Poco::Net::HTTPServerResponse &, const std::string & message);
        void routeHttpMethod(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        static void validateMediaType(Poco::Net::HTTPServerRequest &);
        static void validateHttpMethod(Poco::Net::HTTPServerRequest &);

    };


} }

#endif
