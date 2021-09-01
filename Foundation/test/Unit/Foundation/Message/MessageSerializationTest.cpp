#include <map>
#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "Foundation/Message/XMLMessage.h"

TEST(MessageTest, MessageXmlSerialization)
{
    using namespace Foundation::Message;

    std::map<std::string, std::string> attributes {
            {"to", "Dean Macfarlane"},
            {"from", "Suleman Wynn"},
            {"subject", "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit."}
        };

    std::string content = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.";

    auto message = std::make_unique<XMLMessage>(content, attributes, "93120f46-a11d-11ea-960a-d46a6af0899d");

    ASSERT_FALSE(message->error());
    ASSERT_EQ(message->body(), content);
    ASSERT_EQ(message->size(), content.size());
    ASSERT_EQ(message->attributes().size(), attributes.size());

    // It prints the XML payload for visualization.
    poco_debugger_msg(message->toXml().c_str());

}
