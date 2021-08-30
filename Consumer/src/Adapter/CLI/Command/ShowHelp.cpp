#include <iostream>
#include "Adapter/CLI/Command/ShowHelp.h"
#include "Foundation/System/Application.h"

namespace Consumer {
namespace CLI {


    ShowHelp::ShowHelp(std::vector<std::string> commandList)
        : availableCommands(std::move(commandList))
    {}

    void ShowHelp::showHelp()
    {
        using namespace Foundation::System;

        std::cout << "How to use: " << Application::CONSUMER_CLI_BINARY_NAME << " [command] [option]\n"
            "Type 'ConsumerManagement' [command] --help' for help on a specific subcommand.\n"
            "It Performs operations regarding the 'consumer' component.\n\n";
    }

    void ShowHelp::showArgumentsHelp()
    {
        std::cout << "available commands:\n";
            for (auto const & command : availableCommands)
                std::cout << "    " << command << std::endl;

        std::cout << "\n";
    }

    int ShowHelp::execute(int, char * [])
    {
        showHelp();
        showArgumentsHelp();
        return EXIT_FAILURE;
    }


} }
