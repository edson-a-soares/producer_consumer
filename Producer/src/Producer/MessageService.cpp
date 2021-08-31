#include <iostream>
#include "Producer/MessageService.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/Message/XMLMessageParser.h"

namespace Producer {

    using Message       = Foundation::Message::XMLMessage;
    using MessageParser = Foundation::Message::XMLMessageParser;

    MessageService::MessageService(Foundation::IPC::MessageBus * bus)
        : messageBus(bus)
    {}

    std::unique_ptr<Message> MessageService::exchange(
        const std::string & to,
        const std::string & from,
        const std::string & subject,
        const std::string & content)
    {
        std::map<std::string, std::string> attributes =
        {
            {"to",      to      },
            {"from",    from    },
            {"subject", subject }
        };

        try {
            auto message = Message(content, attributes);
            messageBus->sendMessage(message.toXml());

            auto parser     = MessageParser();
            auto response   = messageBus->readResponse();

            poco_assert_msg(!response.empty(), "IPC Response can't be empty.");
            return parser.fromXml(response);

        } catch (Poco::Exception & exception) {
            return std::make_unique<Message>(exception.message(), attributes);

        }
    }

}
