#include <map>
#include <string>
#include "Foundation/Message/XMLMessageParser.h"
#include "ConsumerDaemon/MessageBusXMLMessageFactory.h"
#include "Foundation/IPC/ConsumerDefaultMessageBusInformation.h"

namespace ConsumerDaemon {


    std::function<std::string(const std::string &)> MessageBusXMLMessageFactory::messageHandlerFunction()
    {
        using namespace Foundation::Message;

        return [=](const std::string & bufferContent) -> std::string
        {
            std::map<std::string, std::string> attributes =
                {
                    {"to",      ""},
                    {"from",    ""},
                    {"subject", "Re: ... "}
                };

            try {
                auto message = XMLMessageParser().fromXml(bufferContent);

                attributes.at("to").assign(message->attributes().at("from"));
                attributes.at("from").assign(message->attributes().at("to"));
                attributes.at("subject").append(message->attributes().at("subject"));

                auto response = XMLMessage("Your message has been handled on the daemon loop with success.", attributes);
                return response.toXml();

            } catch (Poco::Exception & exception) {
                return XMLMessage(exception.message(), attributes).toXml();
            }
        };
    }

    std::unique_ptr<Foundation::IPC::MessageBusInformationInterface> MessageBusXMLMessageFactory::messageBusInformation()
    {
        return std::make_unique<Foundation::IPC::ConsumerDefaultMessageBusInformation>();
    }


}
