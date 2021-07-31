#ifndef Foundation_IPC_ConsumerDefaultMessageBusInformation_INCLUDED
#define Foundation_IPC_ConsumerDefaultMessageBusInformation_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusInformationInterface.h"

namespace Foundation {
namespace IPC {


    class API ConsumerDefaultMessageBusInformation : public MessageBusInformationInterface {
    public:
        ConsumerDefaultMessageBusInformation() = default;
        ~ConsumerDefaultMessageBusInformation() override = default;

        int channelsLength() override;
        std::string inputChannelName() override;
        std::string outputChannelName() override;

    };


} }

#endif
