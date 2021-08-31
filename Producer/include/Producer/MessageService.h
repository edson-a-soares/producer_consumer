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
        using Message = Foundation::Message::XMLMessage;

    public:
        MessageService() = delete;
        ~MessageService() = default;
        explicit MessageService(Foundation::IPC::MessageBus *);
        std::unique_ptr<Message> exchange(
            const std::string & to,
            const std::string & from,
            const std::string & subject,
            const std::string & content
        );

    private:
        Foundation::IPC::MessageBus * messageBus;

    };


}

#endif
