#include "Poco/LocalDateTime.h"
#include "Adapter/CLI/Engine.h"
#include "Poco/DateTimeFormatter.h"
#include "Adapter/CLI/CommandFactory.h"

namespace Consumer {
namespace CLI {


    Engine::Engine(std::unique_ptr<CommandFactoryInterface> factory)
        : commands(std::move(factory))
    {
        about();
    }

    void Engine::about()
    {
        Poco::LocalDateTime dateTime;
        auto copyrightYear = std::to_string(dateTime.year());

        printHeader(copyrightYear);
    }

    void Engine::printHeader(const std::string & copyrightYear)
    {
        std::cout << "Consumer Management Command Line Interface (CLI).\n"
            "Copyright(C) " + copyrightYear + " Edson A. Soares. All rights reserved. <edson.araujo.soares@gmail.com>\n\n";
    }

    int Engine::dispatch(int argCounter, char *argVector[])
    {
        std::string commandName = argVector[1] == nullptr ? std::string("") : std::string(argVector[1]);
        std::unique_ptr<CommandInterface> extension = commands->createCommand(commandName);

        return extension->execute(argCounter, argVector);
    }


} }
