#include "Poco/URI.h"
#include "Foundation/Util/Path.h"
#include "Foundation/IO/Console.h"
#include "boost/filesystem/path.hpp"
#include "boost/process/search_path.hpp"
#include "Foundation/System/Application.h"
#include "Adapter/Http/Resource/ConsumerDaemonResource.h"

namespace Consumer {
namespace Http {


    void ConsumerDaemonResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Foundation;

        try {
            std::vector<std::string> daemonPIDs;
            daemonPIDs = IO::Console::readRunningPidOf(System::Application::CONSUMER_DAEMON_BINARY_NAME);

            if (daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                return;
            }

        } catch (...) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    }

    void ConsumerDaemonResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }


} }
