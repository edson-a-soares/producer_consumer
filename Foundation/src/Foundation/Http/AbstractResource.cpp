#include "Poco/String.h"
#include "Poco/Exception.h"
#include "Poco/Net/MediaType.h"
#include "Foundation/Http/AbstractResource.h"
#include "Adapter/Validation/AllowedHttpMethods.h"
#include "Adapter/Http/DefaultErrorMessageParser.h"
#include "Adapter/Validation/AcceptedHttpContentTypeHeaders.h"

namespace Foundation {
namespace Http {


    void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType(Poco::Net::MediaType("application/xml"));

        try {
            // @TODO The validations may be grouped in a data structure.
            validateHttpMethod(request);
            validateMediaType(request);
            routeHttpMethod(request, response);

        } catch (Poco::Exception & exception) {
            // @TODO Undo this ugly thing.
            response.setStatusAndReason(static_cast<Poco::Net::HTTPResponse::HTTPStatus>(exception.code()));
            dispatchError(response, exception.message());
        }

        dispatch(response);
    }

    void AbstractResource::routeHttpMethod(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Poco::Net;

        if ( request.getMethod() == HTTPRequest::HTTP_GET )
            this->handle_get(request, response);

        if ( request.getMethod() == HTTPRequest::HTTP_PUT )
            this->handle_put(request, response);

        if ( request.getMethod() == HTTPRequest::HTTP_POST )
            this->handle_post(request, response);

        if ( request.getMethod() == HTTPRequest::HTTP_PATCH )
            this->handle_patch(request, response);

        if ( request.getMethod() == HTTPRequest::HTTP_DELETE )
            this->handle_delete(request, response);

        if ( request.getMethod() == HTTPRequest::HTTP_OPTIONS )
            this->handle_options(request, response);
    }

    void AbstractResource::validateHttpMethod(Poco::Net::HTTPServerRequest & request)
    {
        auto httpMethodValidation = ::Validation::AllowedHttpMethods(request);
        if (!httpMethodValidation.isValid())
            throw Poco::Exception("Method Not Allowed", httpMethodValidation.errorMessage(), 405);
    }

    void AbstractResource::validateMediaType(Poco::Net::HTTPServerRequest & request)
    {
        auto mediaTypeValidation = ::Validation::AcceptedHttpContentTypeHeaders(request);
        if (!mediaTypeValidation.isValid())
            throw Poco::Exception("Unsupported Media Type", mediaTypeValidation.errorMessage(), 415);
    }

    void AbstractResource::dispatchError(Poco::Net::HTTPServerResponse & response, const std::string & message)
    {
        auto messageParser = errorMessageParser();
        if (messageParser == nullptr)
            messageParser = std::make_unique<::Http::DefaultErrorMessageParser>();

        auto errorMessage = messageParser->toXml(
            response.getReason(),
            std::to_string(response.getStatus()),
            Poco::trim(message.substr(message.find(':')+1))
        );

        auto stringError = Poco::trim(errorMessage);
        response.sendBuffer(stringError.data(), stringError.length());
    }

    void AbstractResource::dispatch(Poco::Net::HTTPServerResponse & response)
    {
        if (response.getContentLength() == -1)
            response.setContentLength(Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH);

        if (!response.sent())
            response.send().flush();
    }

    std::unique_ptr<ErrorMessageParserInterface> AbstractResource::errorMessageParser()
    {
        return nullptr;
    }

    void AbstractResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
	    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_patch(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }


} }
