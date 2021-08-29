#ifndef Foundation_System_Console_INCLUDED
#define Foundation_System_Console_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace System {


    class API Console
    {
    public:
        Console() = delete;
        ~Console() = delete;

        static std::vector<std::string> runCommand(const std::vector<std::string> & command);
        static void runBackgroundCommand(const std::vector<std::string> & paths, const std::string & command);
        static std::vector<std::string> runCommand(const std::vector<std::string> & command, const std::string & sentinel);

    };


} }

#endif
