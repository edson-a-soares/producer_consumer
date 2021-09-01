#include "Adapter/Validation/AllowedHttpMethods.h"


namespace Validation {


    AllowedHttpMethods::AllowedHttpMethods(Poco::Net::HTTPRequest & request)
        : _request(request)
    {}

    bool AllowedHttpMethods::isValid()
    {
        return _request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET     ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT     ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST    ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH   ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE  ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS;
    }

    std::string AllowedHttpMethods::errorMessage() const
    {
        return "The requested resource does not support http method.";
    }


}
