#include "Foundation/Util/Path.h"
#include "Foundation/Util/CMakeAutogenerated.h"


namespace Foundation {
namespace Util {


    /*
     * The following constants are defined in the CmakeLists files and
     * made available for the application.
     *
     *  @see cmake/Autogenerated.cmake
     *  @see source/CMakeAutogenerated.h.in
     */
    const std::string Path::APPLICATION_HOME_DIRECTORY_PATH   = addSeparatorTo(CMakeAutogenerated::APPLICATION_HOME_DIRECTORY_PATH);
    const std::string Path::APPLICATION_BINARY_DIRECTORY_PATH = addSeparatorTo(CMakeAutogenerated::APPLICATION_BINARY_DIRECTORY_PATH);


    std::string Path::addSeparatorTo(const std::string & path)
    {
        return path + "/";
    }


} }
