#ifndef Consumer_CLI_Command_ConsumerDaemonStart_INCLUDED
#define Consumer_CLI_Command_ConsumerDaemonStart_INCLUDED

#include <string>
#include "Adapter/CLI/CommandInterface.h"

namespace Consumer {
namespace CLI {


    class ConsumerDaemonStart : public CommandInterface
    {
    public:
        ConsumerDaemonStart();
        void showHelp() override;
        void init(int, char * []);
        void showArgumentsHelp() override;
        int execute(int, char * []) override;

    private:
        int status;
        std::string daemonChannel;

    };


} }

#endif
