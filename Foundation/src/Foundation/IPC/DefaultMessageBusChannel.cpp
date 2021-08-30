#include "Foundation/IPC/DefaultMessageBusChannel.h"

namespace Foundation {
namespace IPC {


    int DefaultMessageBusChannel::length()
    {
        return 25 * 1024;
    }

    std::string DefaultMessageBusChannel::inputName()
    {
        return "__INPUT_CHANNEL__";
    }

    std::string DefaultMessageBusChannel::outputName()
    {
        return "__OUTPUT_CHANNEL__";
    }


} }
