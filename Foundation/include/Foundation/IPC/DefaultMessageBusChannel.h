#ifndef Foundation_IPC_DefaultMessageBusChannel_INCLUDED
#define Foundation_IPC_DefaultMessageBusChannel_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace Foundation {
namespace IPC {


    /**
     * This MessageBus is used for anything out of the production environment, including tests.
     */
    class API DefaultMessageBusChannel : public MessageBusChannelInterface {
    public:
        DefaultMessageBusChannel() = default;
        ~DefaultMessageBusChannel() override = default;

        int length() override;
        std::string inputName() override;
        std::string outputName() override;

    };


} }

#endif
