#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Adapter/Http/Resource/MessageResource.h"

namespace Producer {
namespace Http {


    void MessageResource::handle_post(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        std::string requestBody;
        std::istream & inputStream = request.stream();
        Poco::StreamCopier::copyToString(inputStream, requestBody);

        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }

    void MessageResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "POST, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }


} }
