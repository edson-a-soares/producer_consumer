#ifndef Consumer_CLI_Command_ConsumerDaemonStatus_INCLUDED
#define Consumer_CLI_Command_ConsumerDaemonStatus_INCLUDED

#include <string>
#include "Adapter/CLI/CommandInterface.h"

namespace Consumer {
namespace CLI {


    class ConsumerDaemonStatus : public CommandInterface
    {
    public:
        ConsumerDaemonStatus();
        void showHelp() override;
        void init(int, char * []);
        void showArgumentsHelp() override;
        int execute(int, char * []) override;

    private:
        int status;

    };


} }

#endif
