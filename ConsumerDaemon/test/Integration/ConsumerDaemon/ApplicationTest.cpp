#include "gtest/gtest.h"
#include "ConsumerDaemon/Application.h"
#include "Foundation/IPC/ConsumerDaemon.h"
#include "Foundation/IPC/MessageBusFactory.h"
#include "Foundation/Message/XMLMessageParser.h"
#include "ConsumerDaemon/MessageBusAbstractFactory.h"

class ApplicationTest : public ::testing::Test
{
public:
    ApplicationTest() = default;
    ~ApplicationTest() override = default;

protected:
    void SetUp() final
    {
        message.append("<message>");
            message.append("<id>93120f46-a11d-11ea-960a-d46a6af0899d</id>");
            message.append("<attributes>");
                message.append("<to>Consumer Daemon Loop Lambda.</to>");
                message.append("<from>Application test.</from>");
                message.append("<subject>Would you handle a message to me, please?</subject>");
            message.append("</attributes>");
            message.append("<character number=\"92\"></character>");
            message.append("<body>Neque ipsum quia dolor sit amet, consectetur, adipisci velit.</body>\"");
        message.append("</message>");
    }

    std::string message;

};


TEST_F(ApplicationTest, ContentExchangeWithSuccess)
{
    ::ConsumerDaemon::Application::run(0, false);

    auto abstractFactory = ConsumerDaemon::MessageBusAbstractFactory::create(0);
    auto messageBus = Foundation::IPC::MessageBusFactory::getMessageBus(abstractFactory->messageBusInformation());
    messageBus->disableChannelsManagement();

    for (int i = 0; i < 500; i++) {

        try {
            ASSERT_NO_THROW(messageBus->sendMessage(message));
            auto responseContent = messageBus->readResponse();

            auto messageParser = Foundation::Message::XMLMessageParser();
            auto response = messageParser.fromXml(responseContent);

            ASSERT_EQ(response->body(), "Your message has been handled on the daemon loop with success.");

        } catch (Poco::Exception & exception) {
            std::cout << exception.message() << std::endl;

            ASSERT_NO_THROW(Foundation::IPC::ConsumerDaemon::stopListening());
            messageBus->destroyChannels();
            return;
        }

    }

    ASSERT_NO_THROW(Foundation::IPC::ConsumerDaemon::stopListening());
    messageBus->destroyChannels();
}
