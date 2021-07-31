#include <string>
#include "gtest/gtest.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusFactory.h"

TEST(ConsumerDaemonTest, SingleProcessMessageExchangeWithLoopMonitoring)
{
    using namespace Foundation::IPC;

    auto messageBus = MessageBusFactory::createMessageBus();
    ASSERT_NO_THROW(ConsumerDaemon::startMonitoring(
            [](const std::string & message) -> std::string {
                return message + " was handled the callback!!";
            })
        );

    ASSERT_TRUE(ConsumerDaemon::isMonitoring());

    std::string message  = "Content";
    std::string expectedResponse = message + " was handled the callback!!";

    for (int i = 0; i < 500; i++) {
        ASSERT_NO_THROW(messageBus->sendMessage(message));
        ASSERT_EQ(messageBus->readResponse(), expectedResponse);
    }

    ASSERT_NO_THROW(ConsumerDaemon::stopMonitoring());
}

TEST(ConsumerDaemonTest, SingleProcessMessageExchangeWithLoopMonitoringAlternativeFunctionVersion)
{
    using namespace Foundation::IPC;

    auto messageBus = MessageBusFactory::createMessageBus();
    ASSERT_NO_THROW(ConsumerDaemon::startMonitoring(
            [](const std::string & message) -> std::string {
                return message + " was handled the callback!!";
            })
        );

    ASSERT_TRUE(ConsumerDaemon::isMonitoring());

    std::string message  = "Content";
    bool successfullyHandled = false;
    std::string expectedResponse = message + " was handled the callback!!";

    for (int i = 0; i < 500; i++) {
        ASSERT_NO_THROW(messageBus->sendMessage(
                message,
                [=, &successfullyHandled](const std::string & actualResponse) {
                    successfullyHandled = actualResponse == expectedResponse;
                }
            ));

        ASSERT_TRUE(successfullyHandled);

    }

    ASSERT_NO_THROW(ConsumerDaemon::stopMonitoring());
}
