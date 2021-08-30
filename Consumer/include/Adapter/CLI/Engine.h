#ifndef Consumer_CLI_Engine_INCLUDED
#define Consumer_CLI_Engine_INCLUDED

#include <set>
#include <string>
#include <memory>
#include <iostream>
#include "Adapter/CLI/CommandFactoryInterface.h"

namespace Consumer {
namespace CLI {


    class Engine
    {
    public:
        Engine() = delete;
        explicit Engine(std::unique_ptr<CommandFactoryInterface> factory);
        int dispatch(int, char * []);

    private:
        void about();
        void printHeader(const std::string & copyrightYear);

        std::unique_ptr<CommandFactoryInterface> commands;

    };


} }

#endif
