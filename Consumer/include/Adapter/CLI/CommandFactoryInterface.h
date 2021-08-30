#ifndef Consumer_CLI_CommandFactoryInterface_INCLUDED
#define Consumer_CLI_CommandFactoryInterface_INCLUDED

#include "Adapter/CLI/CommandInterface.h"

namespace Consumer {
namespace CLI {


    class CommandFactoryInterface
    {
    public:
        virtual ~CommandFactoryInterface() = default;
        virtual std::unique_ptr<CommandInterface> createCommand(const std::string & name) = 0;

    };


} }

#endif
