#ifndef Foundation_Message_XMLMessageParser_INCLUDED
#define Foundation_Message_XMLMessageParser_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/Message/Message.h"
#include "Foundation/Util/XmlDeserializableInterface.h"

namespace Foundation {
namespace Message {


    class API MessageParser :
        public Util::XmlDeserializableInterface<Message>
    {
    public:
        MessageParser() = default;
        std::unique_ptr<Message> fromXml(const std::string & xml) final;

    };


} }

#endif
