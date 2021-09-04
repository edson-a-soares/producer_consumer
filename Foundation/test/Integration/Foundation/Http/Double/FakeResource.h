#ifndef Foundation_Http_Double_FakeAnyConcreteResource_INCLUDED
#define Foundation_Http_Double_FakeAnyConcreteResource_INCLUDED

#include <memory>
#include "Foundation/Http/AbstractResource.h"
#include "Foundation/Http/Double/EscapedErrorMessageParser.h"

namespace Foundation {
namespace Http {


    class FakeResource : public Foundation::Http::AbstractResource
    {
    protected:
        std::unique_ptr<ErrorMessageParserInterface> errorMessageParser() override;
        void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_put(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


    std::unique_ptr<ErrorMessageParserInterface> FakeResource::errorMessageParser()
    {
        return std::make_unique<EscapedErrorMessageParser>();
    }

    void FakeResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & reponse)
    {
        reponse.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        std::ostream & outputStream = reponse.send();
        outputStream << "{}";
        outputStream.flush();
    }

    void FakeResource::handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
    {
        throw Poco::SyntaxException("Bad Request", "You sent a request that this server could not understand.", 400);
    }

    void FakeResource::handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        auto resourceLocation = "http://localhost?key=value";

        response.set("Content-Location", resourceLocation);
        response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
    }

    void FakeResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, POST, PUT, OPTIONS, PATCH");
    }


} }

#endif
