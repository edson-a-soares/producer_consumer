#ifndef Foundation_Util_Path_INCLUDED
#define Foundation_Util_Path_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace Util {


    /**
     * This structure makes available application Paths.
     *
     * Some constants used here are defined in the CmakeLists files and made available for
     * the application after the build. The constants here are a means of encapsulation for CMakes constants.
     */
    struct API Path
    {
        const static std::string APPLICATION_HOME_DIRECTORY_PATH;
            /// Application directory installation (default.: /usr/local).

        static std::string addSeparatorTo(const std::string & path);

    };


} }

#endif
