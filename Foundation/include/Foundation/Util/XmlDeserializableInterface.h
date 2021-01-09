#ifndef Foundation_Util_XmlDeserializableInterface_INCLUDED
#define Foundation_Util_XmlDeserializableInterface_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Util {


    template<class T>
    class API XmlDeserializableInterface
    {
    public:
        virtual ~XmlDeserializableInterface() = default;
        virtual std::unique_ptr<T> fromXml(const std::string & xml) = 0;

    };


} }

#endif
