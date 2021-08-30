#ifndef Foundation_IPC_MainMessageBusChannel_INCLUDED
#define Foundation_IPC_MainMessageBusChannel_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace Foundation {
namespace IPC {


    /**
     * It is the production MessageBus channel.
     */
    class API MainMessageBusChannel : public MessageBusChannelInterface {
    public:
        MainMessageBusChannel() = default;
        ~MainMessageBusChannel() override = default;

        int length() override;
        std::string inputName() override;
        std::string outputName() override;

    };


} }

#endif
