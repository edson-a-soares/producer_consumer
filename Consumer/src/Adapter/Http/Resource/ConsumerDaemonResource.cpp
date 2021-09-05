#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Foundation/Util/Path.h"
#include "Foundation/IO/Console.h"
#include "boost/process/child.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/process/search_path.hpp"
#include "Foundation/System/Application.h"
#include "Adapter/Http/Resource/ConsumerDaemonResource.h"

namespace Consumer {
namespace Http {


    void ConsumerDaemonResource::handle_post(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Foundation;

        std::string requestBody;
        std::string daemonChannel;
        std::vector<std::string> daemonPIDs;
        std::istream & inputStream = request.stream();
        std::vector<boost::filesystem::path> paths = {
            Util::Path::APPLICATION_BINARY_DIRECTORY_PATH,
            boost::filesystem::current_path().string()
        };

        Poco::StreamCopier::copyToString(inputStream, requestBody);
        if (!requestBody.empty())
            daemonChannel = daemonChannelParameter(requestBody);

        try {
            daemonPIDs = IO::Console::readRunningPidOf(System::Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_CONFLICT);
                return;
            }

            auto consumerDaemon = boost::process::search_path(System::Application::CONSUMER_DAEMON_BINARY_NAME, paths);
            boost::process::child daemon(consumerDaemon, daemonChannel);
            daemon.detach();

            daemonPIDs = IO::Console::readRunningPidOf(System::Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
                return;
            }

        } catch (...) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    void ConsumerDaemonResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Foundation;

        try {
            std::vector<std::string> daemonPIDs = IO::Console::readRunningPidOf(
                System::Application::CONSUMER_DAEMON_BINARY_NAME
                );

            if (daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                return;
            }

        } catch (...) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    }

    void ConsumerDaemonResource::handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        using namespace Foundation;

        std::vector<std::string> daemonPIDs;
        try {
            daemonPIDs = IO::Console::readRunningPidOf(System::Application::CONSUMER_DAEMON_BINARY_NAME);
            if (daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                return;
            }

            while (!daemonPIDs.empty()) {
                kill(std::stoi(daemonPIDs.back()), SIGINT);
                daemonPIDs.pop_back();
            }

            daemonPIDs = IO::Console::readRunningPidOf(System::Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty()) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_ACCEPTED);
                return;
            }

        } catch (...) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    void ConsumerDaemonResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "POST, GET, DELETE, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }

    std::string ConsumerDaemonResource::daemonChannelParameter(const std::string & requestBody)
    {
        Poco::URI uri;
        uri.setQuery(requestBody);
        auto query = uri.getQueryParameters();

        if (query.empty() || query.at(0).first != "daemon_channel")
            throw Poco::IllegalStateException(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);

        return query.at(0).second;
    }


} }
