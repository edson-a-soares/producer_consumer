#include <regex>
#include <memory>
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeList.h"
#include "Foundation/Message/XMLMessage.h"
#include "Foundation/Message/XMLMessageParser.h"

namespace Foundation {
namespace Message {


    std::unique_ptr<XMLMessage> XMLMessageParser::fromXml(const std::string & xml)
    {
        poco_assert_msg(!xml.empty(), "XML document must exit and be valid.");

        Poco::XML::DOMParser parser;

        std::regex expression(">[\\s\r\n]*<");
        auto content = std::regex_replace(xml, expression, "><");

        auto document = parser.parseString(content);

        auto idElement = document->getElementsByTagName("id");
        if ( idElement == nullptr || idElement->length() == 0 )
            throw Poco::InvalidArgumentException("Message ID tag is missing.");

        auto bodyElement = document->getElementsByTagName("body");
        if ( bodyElement == nullptr || bodyElement->length() == 0 )
            throw Poco::InvalidArgumentException("Body tag is missing.");

        auto attributesElement = document->getElementsByTagName("attributes");
        auto attributes = attributesElement->item(0);
        auto nodes = attributes->childNodes();
        if ( nodes == nullptr || nodes->length() != XMLMessage::REQUIRED_ATTRIBUTES_NUMBER )
            throw Poco::InvalidArgumentException("Invalid number of message attributes.");

        auto id   = idElement->item(0)->innerText();
        auto body = bodyElement->item(0)->innerText();

        std::map<std::string, std::string> attributesMap;
        for ( unsigned long item = 0; item < nodes->length(); item++)
            attributesMap.insert({nodes->item(item)->nodeName(), nodes->item(item)->innerText()});

        return std::make_unique<Foundation::Message::XMLMessage>(body, attributesMap, id);
    }


} }
