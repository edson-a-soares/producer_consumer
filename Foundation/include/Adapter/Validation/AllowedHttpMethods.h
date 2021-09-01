#ifndef Validation_AllowedHttpMethods_INCLUDED
#define Validation_AllowedHttpMethods_INCLUDED

#include "Poco/Net/HTTPRequest.h"
#include "Foundation/Foundation.h"
#include "Foundation/Validation/ValidationInterface.h"

namespace Validation {


    class API AllowedHttpMethods : public Foundation::Validation::ValidationInterface
    {
    public:
        explicit AllowedHttpMethods(Poco::Net::HTTPRequest &);
        bool isValid() override;
        std::string errorMessage() const override;

    private:
        Poco::Net::HTTPRequest & _request;

    };


}

#endif
