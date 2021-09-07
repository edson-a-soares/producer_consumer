#include <utility>
#include <iostream>
#include "Producer/MessageService.h"
#include "Foundation/IPC/MessageBus.h"
#include "Foundation/Message/XMLMessageParser.h"

namespace Producer {


    MessageService::MessageService(std::shared_ptr<Foundation::IPC::MessageBus> bus)
        : messageBus(std::move(bus))
    {}

    std::unique_ptr<Foundation::Message::XMLMessage> MessageService::exchange(const std::string & payload)
    {
        using namespace Foundation::Message;

        poco_assert_msg(!payload.empty(), "Payload can't be empty.");

        auto parser  = XMLMessageParser();
        auto message = parser.fromXml(payload);
        messageBus->sendMessage(message->toXml());

        auto response = messageBus->readResponse();
        poco_assert_msg(!response.empty(), "IPC Response can't be empty.");
        return parser.fromXml(response);
    }

    std::unique_ptr<Foundation::Message::XMLMessage> MessageService::exchange(
        const std::string & to,
        const std::string & from,
        const std::string & subject,
        const std::string & content)
    {
        using namespace Foundation::Message;

        std::map<std::string, std::string> attributes =
        {
            {"to",      to      },
            {"from",    from    },
            {"subject", subject }
        };

        try {
            auto message = XMLMessage(content, attributes);
            messageBus->sendMessage(message.toXml());

            auto parser     = XMLMessageParser();
            auto response   = messageBus->readResponse();

            poco_assert_msg(!response.empty(), "IPC Response can't be empty.");
            return parser.fromXml(response);

        } catch (Poco::Exception & exception) {
            return std::make_unique<XMLMessage>(exception.displayText(), attributes);
        }
    }

}
