#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <Poco/Exception.h>
#include "Foundation/Util/Path.h"
#include "Adapter/CLI/Commands.h"
#include "Foundation/IO/Console.h"
#include "boost/process/child.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/process/search_path.hpp"
#include "Foundation/System/Application.h"
#include "Adapter/CLI/Command/ConsumerDaemonStart.h"

namespace Consumer {
namespace CLI {


    ConsumerDaemonStart::ConsumerDaemonStart()
        : status(EXIT_SUCCESS),
          daemonChannel()
    {}

    void ConsumerDaemonStart::showHelp()
    {
        using namespace Foundation::System;

        std::cout << "How to: " << Application::CONSUMER_CLI_BINARY_NAME << " " << Commands::CONSUMER_DAEMON_START << " [option]\n"
            "It starts the " << Application::CONSUMER_DAEMON_BINARY_NAME << " making available the consumer resources.\n" << std::endl;
    }

    void ConsumerDaemonStart::showArgumentsHelp()
    {
        std::cout << "available options: \n"
            "    -c, --channel                 It runs the consumer daemon loop on a specific channel.\n"
            "    -h, --help                    It shows help.\n"
        "\n";
    }

    void ConsumerDaemonStart::init(int argCounter, char * argVector[])
    {
        const char * shortOptions = "c:h";
        const struct option longOptions[] =
        {
            { "channel",            required_argument, nullptr, 'c' },
            { "help",               no_argument,       nullptr, 'h' },
            { nullptr,              0,         nullptr, 0   },
        };

        while(true) {

            const int optionIndex = getopt_long(argCounter, argVector, shortOptions, longOptions, nullptr);

            // no more arguments
            if ( -1 == optionIndex ) break;

            switch(optionIndex)
            {

                case 0:     // long options without short correspondent
                    break;

                case 'c':
                    if ( optarg == nullptr ) {
                        fprintf(stderr, "%s is an invalid value for the option -%c\n", optarg, optionIndex);
                        fprintf(stderr, "Try `%s --help' for more information.\n\n", argVector[0]);
                        exit(EXIT_FAILURE);
                    }
                    daemonChannel = std::string(optarg);
                    break;

                case 'h':
                case '?':
                    showHelp();
                    showArgumentsHelp();
                    exit(EXIT_FAILURE);

                default:
                    fprintf(stderr, "%s: invalid option --%c\n", argVector[0], optionIndex);
                    fprintf(stderr, "Try `%s api start --help' for more information.\n\n", argVector[0]);
                    exit(EXIT_FAILURE);

            }

        }

    }

    int ConsumerDaemonStart::execute(int argCounter, char * argVector[])
    {
        using namespace Foundation;
        using namespace Foundation::IO;
        using namespace Foundation::System;

        init(argCounter, argVector);
        try {
            std::vector<std::string> daemonPIDs = {};
            daemonPIDs = Console::readRunningPidOf(Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty()) {
                std::cout << "It is already running." << std::endl;
                return status;
            }

            std::vector<boost::filesystem::path> paths = {
                Util::Path::APPLICATION_BINARY_DIRECTORY_PATH,
                Util::Path::addDirectoryTo(Util::Path::APPLICATION_HOME_DIRECTORY_PATH, "bin")
            };

            auto consumerDaemon = boost::process::search_path(Application::CONSUMER_DAEMON_BINARY_NAME, paths);
            if (!exists(consumerDaemon)) {
                std::cout << Application::CONSUMER_DAEMON_BINARY_NAME << " not found in the path." << std::endl;
                return EXIT_FAILURE;
            }

            boost::process::child daemon(consumerDaemon, daemonChannel);
            daemon.detach();

            if (daemon.valid() && daemon.running())
                std::cout << "Ok. It is running." << std::endl;

        } catch (...) {
            status = EXIT_FAILURE;
        }

        return status;
    }


} }
