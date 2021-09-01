#include "Adapter/Validation/AcceptedHttpContentTypeHeaders.h"


namespace Validation {


    AcceptedHttpContentTypeHeaders::AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest & request)
        : _request(request),
          HTTP_CONTENT_TYPE("application/xml")
    {}

    bool AcceptedHttpContentTypeHeaders::isValid()
    {
        return _request.getContentType() == HTTP_CONTENT_TYPE;
    }

    std::string AcceptedHttpContentTypeHeaders::errorMessage() const
    {
        return "The only Content Type supported is " + HTTP_CONTENT_TYPE;
    }


}
