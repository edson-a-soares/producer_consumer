#ifndef Foundation_Http_ErrorMessageParserInterface_INCLUDED
#define Foundation_Http_ErrorMessageParserInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Http {


    class API ErrorMessageParserInterface
    {
    public:
        virtual std::string toXml(
            const std::string & type,
            const std::string & status,
            const std::string & detail
        ) = 0;

    };


} }

#endif
