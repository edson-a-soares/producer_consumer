#ifndef Consumer_CLI_Commands_INCLUDED
#define Consumer_CLI_Commands_INCLUDED

#include <vector>
#include <string>

namespace Consumer {
namespace CLI {


    class Commands
    {
    public:
        Commands() = delete;
        ~Commands() = delete;

        static constexpr const char * CONSUMER_DAEMON_STOP              = "consumer_daemon_stop";
        static constexpr const char * CONSUMER_DAEMON_START               = "consumer_daemon_start";
        static constexpr const char * CONSUMER_DAEMON_STATUS            = "consumer_daemon_status";
        static constexpr const char * STANDALONE_MESSAGE_BUS            = "standalone_messagebus";

        static std::vector<std::string> list();

    };


} }

#endif
