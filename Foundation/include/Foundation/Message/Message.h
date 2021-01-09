#ifndef Foundation_Message_Message_INCLUDED
#define Foundation_Message_Message_INCLUDED

#include <map>
#include <string>
#include <experimental/optional>
#include "Foundation/Foundation.h"
#include "Foundation/Message/MessageInterface.h"
#include "Foundation/Message/AbstractXmlMessage.h"
#include "Foundation/Util/XmlSerializableInterface.h"
#include "Foundation/Util/XmlDeserializableInterface.h"

namespace Foundation {
namespace Message {


    class API Message :
        public MessageInterface,
        public AbstractXmlMessage,
        public Util::XmlSerializableInterface
    {
        template<class T> using optional = std::experimental::optional<T>;

    public:
        Message() = delete;
        Message(
            std::string body,
            std::map<std::string, std::string> & attributes,
            optional<std::string> id = std::experimental::nullopt,
            bool error = false
        );

        int size() final;
        bool error() final;
        std::string body() final;
        std::string toXml() final;
        std::map<std::string, std::string> attributes() const final;

        static const int MAXIMUM_SIZE_ALLOWED = 500;
        static const int REQUIRED_ATTRIBUTES_NUMBER = 3;

    private:
            bool _error;
            int _bodySize;
            std::string _body;
            std::map<std::string, std::string> _attributes;

    };


} }

#endif
