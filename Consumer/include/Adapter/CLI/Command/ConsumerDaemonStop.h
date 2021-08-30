#ifndef Consumer_CLI_Command_ConsumerDaemonStop_INCLUDED
#define Consumer_CLI_Command_ConsumerDaemonStop_INCLUDED

#include <string>
#include "Adapter/CLI/CommandInterface.h"

namespace Consumer {
namespace CLI {


    class ConsumerDaemonStop : public CommandInterface
    {
    public:
        ConsumerDaemonStop();
        void showHelp() override;
        void init(int, char * []);
        void showArgumentsHelp() override;
        int execute(int, char * []) override;

    private:
        int status;

    };


} }

#endif
