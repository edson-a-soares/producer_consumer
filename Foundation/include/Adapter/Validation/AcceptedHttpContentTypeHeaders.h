#ifndef Validation_AcceptedHttpContentTypeHeaders_INCLUDED
#define Validation_AcceptedHttpContentTypeHeaders_INCLUDED

#include <vector>
#include <string>
#include "Poco/Net/HTTPRequest.h"
#include "Foundation/Foundation.h"
#include "Foundation/Util/ValidationInterface.h"

namespace Foundation {
namespace Validation {


    class API AcceptedHttpContentTypeHeaders : public Foundation::Util::ValidationInterface
    {
    public:
        explicit AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest &);
        bool isValid() override;
        std::string errorMessage() const override;

    private:
        Poco::Net::HTTPRequest & _request;
        std::vector<std::string> contentTypes;

    };


} }

#endif
