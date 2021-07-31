#ifndef Foundation_IPC_MessageBusFactory_INCLUDED
#define Foundation_IPC_MessageBusFactory_INCLUDED

#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/IPC/MessageBusInformationInterface.h"

namespace Foundation {
namespace IPC {


    class API MessageBusFactory {
    public:
        static std::shared_ptr<MessageBus> getMessageBus(std::unique_ptr<MessageBusInformationInterface> information);

    };


} }

#endif
