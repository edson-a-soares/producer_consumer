#include "Foundation/IPC/ConsumerDaemonMessageBusChannel.h"

namespace Foundation {
namespace IPC {


    int ConsumerDaemonMessageBusChannel::length()
    {
        return 25 * 1024;
    }

    std::string ConsumerDaemonMessageBusChannel::inputName()
    {
        return "__CONSUMER_DAEMON_INPUT_CHANNEL__";
    }

    std::string ConsumerDaemonMessageBusChannel::outputName()
    {
        return "__CONSUMER_DAEMON_OUTPUT_CHANNEL__";
    }


} }
