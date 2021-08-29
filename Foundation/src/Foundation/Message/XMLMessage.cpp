#include <regex>
#include "Foundation/Message/XMLMessage.h"

namespace Foundation {
namespace Message {


    XMLMessage::XMLMessage(
        std::string body,
        std::map<std::string, std::string> & attributes,
        std::experimental::optional<std::string> id,
        bool error
    ) : XMLMessage::AbstractXmlMessage("message"),
          _error(error),
          _bodySize(0),
          _body(std::move(body)),
          _attributes(attributes)
    {
        poco_assert_msg(!_body.empty() && _body.size() < MAXIMUM_SIZE_ALLOWED, "Invalid body value.");
        poco_assert_msg(!_attributes.empty() && _attributes.size() == REQUIRED_ATTRIBUTES_NUMBER, "Invalid attributes.");

        _bodySize = _body.size();
        set("message", "body", _body);
        attributeValue("character", "number", std::to_string(_bodySize));

        if (id)
            AbstractXmlMessage::id(id.value());

        for (auto const & property : _attributes)
            set("attributes", property.first, property.second);
    }

    bool XMLMessage::error() {
        return _error;
    }

    std::map<std::string, std::string> XMLMessage::attributes() const
    {
        return _attributes;
    }

    std::string XMLMessage::body() {
        return _body;
    }

    std::string XMLMessage::toXml() {
        return eraseFormatting(buildXML());
    }

    int XMLMessage::size() {
        return _bodySize;
    }

    std::string XMLMessage::eraseFormatting(const std::string & content)
    {
        std::regex expression(">[\\s\r\n]*<");
        return std::regex_replace(content, expression, "><");
    }


} }
