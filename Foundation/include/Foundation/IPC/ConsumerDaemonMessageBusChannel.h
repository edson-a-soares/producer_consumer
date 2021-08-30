#ifndef Foundation_IPC_ConsumerDaemonMessageBusChannel_INCLUDED
#define Foundation_IPC_ConsumerDaemonMessageBusChannel_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace Foundation {
namespace IPC {


    /**
     * Production environment MessageBus data.
     */
    class API ConsumerDaemonMessageBusChannel : public MessageBusChannelInterface {
    public:
        ConsumerDaemonMessageBusChannel() = default;
        ~ConsumerDaemonMessageBusChannel() override = default;

        int length() override;
        std::string inputName() override;
        std::string outputName() override;

    };


} }

#endif
