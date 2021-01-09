#ifndef Foundation_Message_MessageInterface_INCLUDED
#define Foundation_Message_MessageInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Message {


    class API MessageInterface
    {
    public:
        virtual ~MessageInterface() = default;
        virtual int size() = 0;
        virtual bool error() = 0;
        virtual std::string body() = 0;
        virtual std::map<std::string, std::string> attributes() const = 0;

    };


} }

#endif
