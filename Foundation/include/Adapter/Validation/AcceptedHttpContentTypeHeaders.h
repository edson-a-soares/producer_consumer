#ifndef Validation_AcceptedHttpContentTypeHeaders_INCLUDED
#define Validation_AcceptedHttpContentTypeHeaders_INCLUDED

#include "Poco/Net/HTTPRequest.h"
#include "Foundation/Foundation.h"
#include "Foundation/Util/ValidationInterface.h"

namespace Validation {


    class API AcceptedHttpContentTypeHeaders : public Foundation::Util::ValidationInterface
    {
    public:
        explicit AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest &);
        bool isValid() override;
        std::string errorMessage() const override;

    private:
        Poco::Net::HTTPRequest & _request;
        const std::string HTTP_CONTENT_TYPE;

    };


}

#endif
