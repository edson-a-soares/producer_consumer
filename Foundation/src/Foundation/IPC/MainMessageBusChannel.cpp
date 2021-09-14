#include "Foundation/IPC/MainMessageBusChannel.h"

namespace Foundation {
namespace IPC {


    int MainMessageBusChannel::length()
    {
        return 50 * 1024;
    }

    std::string MainMessageBusChannel::inputName()
    {
        return "__CONSUMER_DAEMON_INPUT_CHANNEL__";
    }

    std::string MainMessageBusChannel::outputName()
    {
        return "__CONSUMER_DAEMON_OUTPUT_CHANNEL__";
    }


} }
