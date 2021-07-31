#ifndef Foundation_IPC_MessageBusFactory_INCLUDED
#define Foundation_IPC_MessageBusFactory_INCLUDED

#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/IPC/MessageBusDataInterface.h"

namespace Foundation {
namespace IPC {


    class API MessageBusFactory {
    public:
        static std::shared_ptr<MessageBus> createMessageBus();

    };


} }

#endif
