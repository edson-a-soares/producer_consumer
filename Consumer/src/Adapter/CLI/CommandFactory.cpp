#include "Adapter/CLI/Commands.h"
#include "Adapter/CLI/CommandFactory.h"
#include "Adapter/CLI/Command/ShowHelp.h"
#include "Adapter/CLI/Command/ConsumerDaemonStop.h"
#include "Adapter/CLI/Command/ConsumerDaemonStart.h"
#include "Adapter/CLI/Command/ConsumerDaemonStatus.h"

namespace Consumer {
namespace CLI {


    std::unique_ptr<CommandInterface> CommandFactory::createCommand(const std::string & index)
    {
        std::unique_ptr<CommandInterface> command = nullptr;

        if (index == Commands::CONSUMER_DAEMON_STOP)
            command = std::make_unique<ConsumerDaemonStop>();

        if (index == Commands::CONSUMER_DAEMON_START)
            command = std::make_unique<ConsumerDaemonStart>();

        if (index == Commands::CONSUMER_DAEMON_STATUS)
            command = std::make_unique<ConsumerDaemonStatus>();

        if (command == nullptr)
            command = std::make_unique<ShowHelp>(Commands::list());

        return command;
    }


} }
