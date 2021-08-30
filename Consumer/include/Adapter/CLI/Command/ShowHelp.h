#ifndef Consumer_CLI_Command_ShowHelp_INCLUDED
#define Consumer_CLI_Command_ShowHelp_INCLUDED

#include <vector>
#include "Adapter/CLI/CommandInterface.h"

namespace Consumer {
namespace CLI {


    class ShowHelp : public CommandInterface
    {
    public:
        ShowHelp() = delete;
        explicit ShowHelp(std::vector<std::string> commandList);
        void showHelp() override;
        void showArgumentsHelp() override;
        int execute(int, char * []) override;

    private:
        std::vector<std::string> availableCommands;

    };


} }

#endif
