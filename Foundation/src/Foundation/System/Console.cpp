#include <sstream>
#include "Poco/Exception.h"
#include "boost/process.hpp"
#include "boost/process/child.hpp"
#include "Foundation/System/Console.h"

namespace Foundation {
namespace System {


    std::vector<std::string> Console::runCommand(const std::vector<std::string> & command)
    {
        std::string line;
        std::vector<std::string> output;
        boost::process::ipstream inputStream;
        boost::process::child process(command, boost::process::std_out > inputStream);

        while (process.running() && std::getline(inputStream, line) && !line.empty())
            output.push_back(line);

        process.detach();
        return output;
    }

    void Console::runBackgroundCommand(const std::vector<std::string> & paths, const std::string & command)
    {
        std::vector<std::string> commandPIDs            = {};
        std::vector<boost::filesystem::path> boostPaths = {};

        boostPaths.reserve(paths.size());
        for (const std::string & path : paths)
            boostPaths.emplace_back(boost::filesystem::path(path));

        auto commandPath = boost::process::search_path(command, boostPaths);
        boost::process::child backgroundProcess(commandPath);
        backgroundProcess.detach();

        if (!backgroundProcess.running())
            throw Poco::IllegalStateException();
    }

    std::vector<std::string> Console::runCommand(const std::vector<std::string> & command, const std::string & sentinel)
    {
        std::string line;
        boost::process::ipstream inputStream;
        std::vector<std::string> commandOutput;
        boost::process::child process(command, boost::process::std_out > inputStream);

        while (process.running() && std::getline(inputStream, line) && line != sentinel)
            commandOutput.push_back(line);

        process.detach();
        return commandOutput;
    }


} }
