#include "Foundation/IPC/ConsumerDefaultMessageBusInformation.h"

namespace Foundation {
namespace IPC {


    int ConsumerDefaultMessageBusInformation::channelsLength()
    {
        return 25 * 1024;
    }

    std::string ConsumerDefaultMessageBusInformation::inputChannelName()
    {
        return "__INPUT_CHANNEL__";
    }

    std::string ConsumerDefaultMessageBusInformation::outputChannelName()
    {
        return "__OUTPUT_CHANNEL__";
    }


} }
