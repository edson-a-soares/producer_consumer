#include <sstream>
#include "boost/process/child.hpp"
#include "Foundation/IO/Console.h"
#include "Foundation/System/Console.h"

namespace Foundation {
namespace IO {


    std::vector<std::string> Console::readRunningPidOf(const std::string & binaryName)
    {
        std::string pidof = "pidof";
        std::vector<std::string> psIDs;

        pidof.append(" " + binaryName);
        auto output = System::Console::runCommand({ "/bin/sh", "-c", pidof });
        if (output.empty())
            return psIDs;

        /*
         * The command 'pidof' returns all PIDs of running process in just one line separated by spaces.
         * That's why only one instruction .back() from the Vector data structure is enough to get all the information
         * in the data structure.
         */
        std::istringstream inputStream(output.back());

        for( std::string pid; inputStream >> pid; )
            psIDs.emplace_back(pid);

        return psIDs;
    }

    std::map<std::string, std::string> Console::readInformationFrom(const std::string & pid)
    {
        std::ostringstream ps;
        std::map<std::string, std::string> result = {};
        std::vector<std::string> keys = { "pid", "memory", "os_user", "os_group", "command", "time_elapsed", "starting_time" };

        ps << "ps";
        ps << " -p " << pid;
        ps << " -o pid,vsz=MEMORY";
        ps << " -o user,group=GROUP";
        ps << " -o comm";               // displays the name of the command that is executing.
        ps << " -o etime";              // displays the amount of real time that has elapsed since the process began execution.
        ps << " -o stime";              // displays the start time of the process.

        auto rawOutput = System::Console::runCommand({"/bin/sh", "-c", ps.str() });
        auto lastPIDInformation = rawOutput.back();

        auto key = keys.begin();
        std::istringstream inputStream(lastPIDInformation);
        for( std::string info; inputStream >> info; ) {
            result.insert(std::pair<std::string, std::string>(*key, info));
            ++key;
        }

        return result;
    }


} }
