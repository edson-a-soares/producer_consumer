#include <string>
#include "gtest/gtest.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusController.h"

TEST(ConsumerDaemonTest, SingleProcessMessageExchangeWithLoopMonitoring)
{
    using namespace Foundation::IPC;

    auto messageBus = MessageBusController::createMessageBus();
    ASSERT_NO_THROW(ConsumerDaemon::startMonitoring(
            [](const std::string & message) -> std::string {
                return message + " was handled the callback!!";
            })
        );

    std::string message  = "Content";
    std::string expectedResponse = message + " was handled the callback!!";

    for (int i = 0; i < 500; i++) {
        ASSERT_NO_THROW(messageBus->sendMessage(message));
        ASSERT_EQ(messageBus->readResponse(), expectedResponse);
    }

    ASSERT_NO_THROW(ConsumerDaemon::stopMonitoring());
    ASSERT_NO_THROW(MessageBusController::destroyMessageBus());

}
