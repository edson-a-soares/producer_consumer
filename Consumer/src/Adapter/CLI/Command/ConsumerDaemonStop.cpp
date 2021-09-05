#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <getopt.h>
#include <iostream>
#include "Adapter/CLI/Commands.h"
#include "Foundation/IO/Console.h"
#include "Foundation/System/Application.h"
#include "Adapter/CLI/Command/ConsumerDaemonStop.h"

namespace Consumer {
namespace CLI {


    ConsumerDaemonStop::ConsumerDaemonStop()
        : forceStop(false),
          status(EXIT_SUCCESS)
    {}

    void ConsumerDaemonStop::showHelp()
    {
        using namespace Foundation::System;

        std::cout << "How to: " << Application::CONSUMER_CLI_BINARY_NAME << " " << Commands::CONSUMER_DAEMON_STOP << " [option]\n"
            "It stops the " << Application::CONSUMER_DAEMON_BINARY_NAME << ".\n" << std::endl;;
    }

    void ConsumerDaemonStop::showArgumentsHelp()
    {
        std::cout << "available options: \n"
            "    -f, --force        It kills the daemon process immediately.\n"
            "    -h, --help         It shows help.\n"
        "\n";
    }

    void ConsumerDaemonStop::init(int argCounter, char * argVector[])
    {
        const char * shortOptions = "f:h";
        const struct option longOptions[] =
        {
            { "force",              no_argument,       nullptr, 'f' },
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

                case 'h':
                case '?':
                    showHelp();
                    showArgumentsHelp();
                    exit(EXIT_FAILURE);

                case 'f':
                    if ( optarg == nullptr ) {
                        fprintf(stderr, "%s is an invalid value for the option -%c\n", optarg, optionIndex);
                        fprintf(stderr, "Try `%s --help' for more information.\n\n", argVector[0]);
                        exit(EXIT_FAILURE);
                    }
                    forceStop = true;
                    break;

                default:
                    fprintf(stderr, "%s: invalid option --%c\n", argVector[0], optionIndex);
                    fprintf(stderr, "Try `%s api start --help' for more information.\n\n", argVector[0]);
                    exit(EXIT_FAILURE);
            }

        }

    }

    int ConsumerDaemonStop::execute(int argCounter, char * argVector[])
    {
        using namespace Foundation::IO;
        using namespace Foundation::System;

        init(argCounter, argVector);
        try {
            std::vector<std::string> daemonPIDs = {};

            daemonPIDs = Console::readRunningPidOf(Application::CONSUMER_DAEMON_BINARY_NAME);
            if (daemonPIDs.empty()) {
                std::cout << "It is not running." << std::endl;
                return status;
            }

            while (!daemonPIDs.empty()) {
                std::cout << "Stopping the process ID " << daemonPIDs.back() << "." << std::endl;
                kill(std::stoi(daemonPIDs.back()), SIGINT);
                daemonPIDs.pop_back();
            }

            if (forceStop)
                kill(std::stoi(daemonPIDs.back()), SIGKILL);

            daemonPIDs = Console::readRunningPidOf(Application::CONSUMER_DAEMON_BINARY_NAME);
            if (daemonPIDs.empty())
                std::cout << "It is stopped." << std::endl;

        } catch (std::exception & exception) {
            std::cout << exception.what() << std::endl;
            status = EXIT_FAILURE;

        }

        return status;
    }


} }
