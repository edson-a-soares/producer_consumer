#include "Foundation/Message/Message.h"

namespace Foundation {
namespace Message {


    Message::Message(
        std::string body,
        std::map<std::string, std::string> & attributes,
        std::experimental::optional<std::string> id,
        bool error) : Message::AbstractXmlMessage("message"),
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

    bool Message::error() {
        return _error;
    }

    std::map<std::string, std::string> Message::attributes() const
    {
        return _attributes;
    }

    std::string Message::body() {
        return _body;
    }

    std::string Message::toXml() {
        return buildXML();
    }

    int Message::size() {
        return _bodySize;
    }


} }
