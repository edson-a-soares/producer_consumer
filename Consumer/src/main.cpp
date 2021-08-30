#include "Adapter/CLI/Engine.h"
#include "Adapter/CLI/CommandFactory.h"

int main (int argc, char * argv[])
{
    auto factory = std::make_unique<Consumer::CLI::CommandFactory>();

    Consumer::CLI::Engine engine(std::move(factory));
    return engine.dispatch(argc, argv);
}
