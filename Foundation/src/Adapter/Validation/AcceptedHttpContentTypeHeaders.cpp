#include "Adapter/Validation/AcceptedHttpContentTypeHeaders.h"

namespace Foundation {
namespace Validation {


    AcceptedHttpContentTypeHeaders::AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest & request)
        : _request(request),
          contentTypes { "application/xml" }
    {}

    bool AcceptedHttpContentTypeHeaders::isValid()
    {
        return std::count(contentTypes.begin(), contentTypes.end(), _request.getContentType());
    }

    std::string AcceptedHttpContentTypeHeaders::errorMessage() const
    {
        return "Content Type supported is not supported: " + _request.getContentType();
    }


} }
