#ifndef Foundation_Message_XMLMessageParser_INCLUDED
#define Foundation_Message_XMLMessageParser_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/Message/XMLMessage.h"
#include "Foundation/Util/XmlDeserializableInterface.h"

namespace Foundation {
namespace Message {


    class API XMLMessageParser :
        public Util::XmlDeserializableInterface<XMLMessage>
    {
    public:
        XMLMessageParser() = default;
        std::unique_ptr<XMLMessage> fromXml(const std::string & xml) final;

    };


} }

#endif
