#ifndef Consumer_CLI_CommandFactory_INCLUDED
#define Consumer_CLI_CommandFactory_INCLUDED

#include <string>
#include <memory>
#include "Adapter/CLI/CommandFactoryInterface.h"

namespace Consumer {
namespace CLI {


    class CommandFactory : public CommandFactoryInterface
    {
    public:
	    ~CommandFactory() override = default;
        std::unique_ptr<CommandInterface> createCommand(const std::string & name) override;

    };


} }

#endif
