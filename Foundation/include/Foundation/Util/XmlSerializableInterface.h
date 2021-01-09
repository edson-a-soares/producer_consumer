#ifndef Foundation_Util_XmlSerializableInterface_INCLUDED
#define Foundation_Util_XmlSerializableInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Util {


    class API XmlSerializableInterface
    {
    public:
        virtual ~XmlSerializableInterface() = default;
        virtual std::string toXml() = 0;

    };


} }

#endif
