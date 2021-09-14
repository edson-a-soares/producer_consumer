#include "Adapter/Http/DefaultErrorMessageParser.h"
#include "Adapter/Http/DefaultXMLErrorMessage.h"


namespace Foundation {
namespace Http {


    std::string DefaultErrorMessageParser::toXml(const std::string & type, const std::string & status, const std::string & detail)
    {
        return DefaultXMLErrorMessage(type, status, detail).toXml();
    }


} }
