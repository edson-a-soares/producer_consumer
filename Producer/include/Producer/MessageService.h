#ifndef Producer_MessageService_INCLUDED
#define Producer_MessageService_INCLUDED

#include <memory>
#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/Message/XMLMessage.h"

namespace Producer {


    class API MessageService
    {
    public:
        MessageService() = default;
        ~MessageService() = default;
        explicit MessageService(std::shared_ptr<Foundation::IPC::MessageBus>);
        std::unique_ptr<Foundation::Message::XMLMessage> exchange(const std::string & payload);
        std::unique_ptr<Foundation::Message::XMLMessage> exchange(
            const std::string & to,
            const std::string & from,
            const std::string & subject,
            const std::string & content
        );

    private:
        std::shared_ptr<Foundation::IPC::MessageBus> messageBus;

    };


}

#endif
