#include "Adapter/Http/DefaultXMLErrorMessage.h"

namespace Foundation {
namespace Http {


    DefaultXMLErrorMessage::DefaultXMLErrorMessage(
        std::string type,
        std::string status,
        std::string detail,
        std::experimental::optional<std::string> id
    ) : AbstractXmlMessage("http_error"),
          _type(std::move(type)),
          _status(std::move(status)),
          _detail(std::move(detail))
    {
        poco_assert_msg(!_type.empty(), "Invalid error value.");
        poco_assert_msg(!_status.empty(), "Invalid status value.");
        poco_assert_msg(!_detail.empty(), "Invalid detail value.");

        if (id)
            AbstractXmlMessage::id(id.value());

        set("error", "type", _type);
        set("error", "status", _status);
        set("error", "detail", _detail);
    }

    std::string DefaultXMLErrorMessage::toXml() {
        return eraseFormatting(buildXML("error"));
    }


} }
