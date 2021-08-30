#include "Adapter/CLI/Commands.h"

namespace Consumer {
namespace CLI {


    std::vector<std::string> Commands::list()
    {
        std::vector<std::string> allOptions = {
            CONSUMER_DAEMON_START,
            CONSUMER_DAEMON_STOP,
            CONSUMER_DAEMON_STATUS
        };

        return allOptions;
    }


} }
