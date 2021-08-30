#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include "Adapter/CLI/Commands.h"
#include "Foundation/IO/Console.h"
#include "boost/process/child.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/process/search_path.hpp"
#include "Foundation/System/Application.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Adapter/CLI/Command/ConsumerDaemonStart.h"

namespace Consumer {
namespace CLI {


    ConsumerDaemonStart::ConsumerDaemonStart()
        : status(EXIT_SUCCESS),
          responseMessage()
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
            "    -r, --response-message                 It defines a default response message to the daemon loop.\n"
            "    -h, --help                             It shows help.\n"
        "\n";
    }

    void ConsumerDaemonStart::init(int argCounter, char * argVector[])
    {
        const char * shortOptions = "r:h";
        const struct option longOptions[] =
        {
            { "response-message",   required_argument, nullptr, 'r' },
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

                case 'r':
                    if ( optarg == nullptr ) {
                        fprintf(stderr, "%s is an invalid value for the option -%c\n", optarg, optionIndex);
                        fprintf(stderr, "Try `%s consumer channels only --help' for more information.\n\n", argVector[0]);
                        exit(EXIT_FAILURE);
                    }
                    responseMessage = std::string(optarg);
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
        using namespace Foundation::IO;
        using namespace Foundation::IPC;
        using namespace Foundation::System;

        init(argCounter, argVector);
        try {
            std::vector<std::string> daemonPIDs = {};
            std::vector<boost::filesystem::path> paths = {
                boost::filesystem::path("bin")
            };

            daemonPIDs = Console::readRunningPidOf(Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty()) {
                std::cout << "It is already running." << std::endl;
                return status;
            }

            auto consumerDaemon = boost::process::search_path(Application::CONSUMER_DAEMON_BINARY_NAME, paths);
            boost::process::child daemon(consumerDaemon);
            daemon.detach();

            daemonPIDs = Console::readRunningPidOf(Application::CONSUMER_DAEMON_BINARY_NAME);
            if (!daemonPIDs.empty())
                std::cout << "Ok. It is running." << std::endl;

        } catch (...) {
            status = EXIT_FAILURE;
        }

        return status;
    }


} }
