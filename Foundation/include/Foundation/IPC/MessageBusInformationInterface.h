#ifndef Foundation_IPC_MessageBusInformationInterface_INCLUDED
#define Foundation_IPC_MessageBusInformationInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API MessageBusInformationInterface
    {
    public:
        virtual ~MessageBusInformationInterface() = default;
        virtual int channelsLength() = 0;
        virtual std::string inputChannelName() = 0;
        virtual std::string outputChannelName() = 0;

    };


} }

#endif
