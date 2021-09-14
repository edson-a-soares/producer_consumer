#ifndef Foundation_Http_ErrorHandlerBuilderInterface_INCLUDED
#define Foundation_Http_ErrorHandlerBuilderInterface_INCLUDED

#include "Poco/Net/HTTPResponse.h"
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Http {


    class API ErrorHandlerBuilderInterface
    {
    public:
        ~ErrorHandlerBuilderInterface() = default;
        virtual Poco::Net::HTTPRequestHandler * build() = 0;
        virtual ErrorHandlerBuilderInterface & type(std::string) = 0;
        virtual ErrorHandlerBuilderInterface & detail(std::string) = 0;
        virtual ErrorHandlerBuilderInterface & status(Poco::Net::HTTPResponse::HTTPStatus) = 0;

    };


} }

#endif
