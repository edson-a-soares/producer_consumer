#include <iostream>
#include "ConsumerDaemon/Application.h"

int main (int argc, char * argv[])
{
    using namespace ConsumerDaemon;

    std::string option = argv[1] == nullptr ? "" : std::string(argv[1]);
    if (option == "main") {
        ConsumerDaemon::Application::runOn(Application::MAIN_CHANNEL);
        return 0;
    }

    ConsumerDaemon::Application::runOn(Application::DEFAULT_CHANNEL);
    return 0;
}
