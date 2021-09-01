#ifndef Foundation_Http_EscapedErrorMessageParser_INCLUDED
#define Foundation_Http_EscapedErrorMessageParser_INCLUDED

#include <string>
#include "Adapter/Http/DefaultXMLErrorMessage.h"
#include "Foundation/Http/ErrorMessageParserInterface.h"

namespace Foundation {
namespace Http {


    /**
     * Poco HTTPResponse does not sendResponse response messages with whitespaces.
     * This class exists for doing two specific things:
     *   1. Replace whitespaces to underscore characters. So, the response message might be tested.
     *   2. Remove any text appended to the error description (e.g., Exception Stacktrace).
     */
    class EscapedErrorMessageParser : public Foundation::Http::ErrorMessageParserInterface
    {
    public:
        std::string toXml(
            const std::string & type,
            const std::string & status,
            const std::string & detail
        ) override;

    };


    std::string EscapedErrorMessageParser::toXml(
        const std::string & type,
        const std::string & status,
        const std::string & detail
    ) {
        auto xmlMessageObject = ::Http::DefaultXMLErrorMessage(type, status, detail, "0");
        auto errorMessage = xmlMessageObject.toXml();
        std::replace(errorMessage.begin(), errorMessage.end(), ' ', '_');
        return errorMessage;
    }


} }

#endif
