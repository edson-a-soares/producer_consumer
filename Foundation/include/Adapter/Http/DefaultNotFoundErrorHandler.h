#ifndef Http_DefaultNotFoundErrorHandler_INCLUDED
#define Http_DefaultNotFoundErrorHandler_INCLUDED

#include "Foundation/Foundation.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Foundation {
namespace Http {


    class API DefaultNotFoundErrorHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


} }

#endif
