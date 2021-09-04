#ifndef Foundation_Util_ValidationInterface_INCLUDED
#define Foundation_Util_ValidationInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Util {


    class API ValidationInterface
    {
    public:
        virtual ~ValidationInterface() = default;
        virtual bool isValid() = 0;
        virtual std::string errorMessage() const = 0;

    };


} }

#endif
