#ifndef Foundation_IO_Console_INCLUDED
#define Foundation_IO_Console_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IO {


    class API Console
    {
    public:
        Console() = delete;
        ~Console() = delete;

        static std::vector<std::string> readRunningPidOf(const std::string & binaryName);

        /**
         * @see https://www.mkssoftware.com/docs/man1/ps.1.asp#Format_Specifications
         */
        static std::map<std::string, std::string> readInformationFrom(const std::string & pid);

    };


} }

#endif
