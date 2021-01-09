#include <memory>
#include <iostream>
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeList.h"
#include "Foundation/Message/Message.h"
#include "Foundation/Message/MessageParser.h"

namespace Foundation {
namespace Message {


    std::unique_ptr<Message> MessageParser::fromXml(const std::string & xml)
    {
        poco_assert_msg(!xml.empty(), "XML document must exit and be valid.");

        Poco::XML::DOMParser parser;
        auto document = parser.parseString(xml);

        auto idElement = document->getElementsByTagName("id");
        if ( idElement == nullptr || idElement->length() == 0 )
            throw Poco::InvalidArgumentException();

        auto bodyElement = document->getElementsByTagName("body");
        if ( bodyElement == nullptr || bodyElement->length() == 0 )
            throw Poco::InvalidArgumentException();

        auto attributesElement = document->getElementsByTagName("attributes");
        auto attributes = attributesElement->item(0);
        auto nodes  = attributes->childNodes();
        if ( nodes == nullptr || nodes->length() != Message::REQUIRED_ATTRIBUTES_NUMBER )
            throw Poco::InvalidArgumentException();

        auto id   = idElement->item(0)->innerText();
        auto body = bodyElement->item(0)->innerText();

        std::map<std::string, std::string> attributesMap;
        for ( unsigned long item = 0; item < nodes->length(); item++)
            attributesMap.insert({nodes->item(item)->nodeName(), nodes->item(item)->innerText()});

        return std::make_unique<Foundation::Message::Message>(body, attributesMap, id);
    }


} }
