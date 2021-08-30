#include <map>
#include <string>
#include "Foundation/Message/XMLMessageParser.h"
#include "Foundation/IPC/ConsumerDaemonMessageBusChannel.h"
#include "ConsumerDaemon/ConsumerDaemonChannelWithXMLMessageHandlerFactory.h"

namespace ConsumerDaemon {


    std::function<std::string(const std::string &)> ConsumerDaemonChannelWithXMLMessageHandlerFactory::messageHandlerFunction()
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

    std::unique_ptr<Foundation::IPC::MessageBusChannelInterface> ConsumerDaemonChannelWithXMLMessageHandlerFactory::messageBusChannelInformation()
    {
        return std::make_unique<Foundation::IPC::ConsumerDaemonMessageBusChannel>();
    }


}
