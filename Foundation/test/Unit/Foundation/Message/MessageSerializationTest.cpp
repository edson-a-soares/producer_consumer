#include <map>
#include <string>
#include "gtest/gtest.h"
#include "Foundation/Message/XMLMessage.h"

TEST(MessageTest, MessageXmlSerialization)
{

    auto xml =
        "<message>\n"
        "    <id>93120f46-a11d-11ea-960a-d46a6af0899d</id>\n"
        "    <attributes>\n"
        "        <to>Dean Macfarlane</to>\n"
        "        <from>Suleman Wynn</from>\n"
        "        <subject>Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.</subject>\n"
        "    </attributes>\n"
        "    <character number=\"92\"></character>\n"
        "    <body>Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.</body>\n"
        "</message>";

    std::map<std::string, std::string> attributes {
            {"to", "Dean Macfarlane"},
            {"from", "Suleman Wynn"},
            {"subject", "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit."}
        };

    std::string content = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.";

    auto message = Foundation::Message::XMLMessage(content, attributes, "93120f46-a11d-11ea-960a-d46a6af0899d");


    ASSERT_EQ(message.toXml(), xml);
    ASSERT_FALSE(message.error());
    ASSERT_EQ(message.body(), content);
    ASSERT_EQ(message.size(), content.size());
    ASSERT_EQ(message.attributes().size(), attributes.size());


    // It prints the XML payload for visualization.
    std::cout << std::endl << message.toXml() << std::endl;


}
