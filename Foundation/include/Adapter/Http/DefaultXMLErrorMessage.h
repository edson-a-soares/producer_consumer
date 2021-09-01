#ifndef Http_DefaultXMLErrorMessage_INCLUDED
#define Http_DefaultXMLErrorMessage_INCLUDED

#include <string>
#include <experimental/optional>
#include "Foundation/Foundation.h"
#include "Foundation/Message/AbstractXmlMessage.h"
#include "Foundation/Util/XmlSerializableInterface.h"

namespace Http {


    class API DefaultXMLErrorMessage :
        public Foundation::Message::AbstractXmlMessage,
        public Foundation::Util::XmlSerializableInterface
    {
        template<class T> using optional = std::experimental::optional<T>;

    public:
        DefaultXMLErrorMessage() = delete;
        DefaultXMLErrorMessage(
            std::string type,
            std::string status,
            std::string detail,
            optional<std::string> id = std::experimental::nullopt
        );

        std::string toXml() override;

    private:
        std::string _type;
        std::string _status;
        std::string _detail;

    };


}

#endif
