#ifndef Foundation_IPC_MessageBusController_INCLUDED
#define Foundation_IPC_MessageBusController_INCLUDED

#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBus.h"

namespace Foundation {
namespace IPC {


    class API MessageBusController {
    public:
        static void destroyMessageBus();
        static std::shared_ptr<MessageBus> createMessageBus();

    };


} }

#endif
