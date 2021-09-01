#ifndef Http_DefaultErrorMessageParser_INCLUDED
#define Http_DefaultErrorMessageParser_INCLUDED

#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/Http/ErrorMessageParserInterface.h"

namespace Http {


    class API DefaultErrorMessageParser : public Foundation::Http::ErrorMessageParserInterface
    {
    public:
        std::string toXml(
            const std::string & type,
            const std::string & status,
            const std::string & detail
        ) override;

    };


}

#endif
