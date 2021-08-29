#include <string>
#include "gtest/gtest.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusFactory.h"
#include "Foundation/IPC/ConsumerDefaultMessageBusInformation.h"

TEST(ConsumerDaemonTest, SingleProcessExchangeLoopMonitoring)
{
    using namespace Foundation::IPC;

    ASSERT_NO_THROW(ConsumerDaemon::startListening(
            std::make_unique<ConsumerDefaultMessageBusInformation>(),
            [](const std::string & message) -> std::string {
                return message + " was handled by the callback!!";
            })
        );

    ASSERT_TRUE(ConsumerDaemon::isListening());

    std::string message  = "Content";
    std::string expectedResponse = message + " was handled by the callback!!";

    auto messageBus = MessageBusFactory::getMessageBus(std::make_unique<ConsumerDefaultMessageBusInformation>());
    for (int i = 0; i < 500; i++) {
        ASSERT_NO_THROW(messageBus->sendMessage(message));
        ASSERT_EQ(messageBus->readResponse(), expectedResponse);
    }

    ASSERT_NO_THROW(ConsumerDaemon::stopListening());
}

TEST(ConsumerDaemonTest, SingleProcessExchangeWithLoopMonitoringAlternativeHandlerVersion)
{
    using namespace Foundation::IPC;

    ASSERT_NO_THROW(ConsumerDaemon::startListening(
            std::make_unique<ConsumerDefaultMessageBusInformation>(),
            [](const std::string & message) -> std::string {
                return message + " was handled the callback!!";
            })
        );

    ASSERT_TRUE(ConsumerDaemon::isListening());

    std::string message  = "Content";
    bool successfullyHandled = false;
    std::string expectedResponse = message + " was handled the callback!!";

    auto messageBus = MessageBusFactory::getMessageBus(std::make_unique<ConsumerDefaultMessageBusInformation>());
    for (int i = 0; i < 500; i++) {
        ASSERT_NO_THROW(messageBus->sendMessage(
                message,
                [=, &successfullyHandled](const std::string & actualResponse) {
                    successfullyHandled = actualResponse == expectedResponse;
                }
            ));

        ASSERT_TRUE(successfullyHandled);

    }

    ASSERT_NO_THROW(ConsumerDaemon::stopListening());
}
