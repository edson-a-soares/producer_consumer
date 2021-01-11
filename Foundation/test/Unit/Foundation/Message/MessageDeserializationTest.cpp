#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "Foundation/Message/XMLMessageParser.h"

TEST(MessageTest, MessageXmlDeserialization)
{
    using namespace Foundation::Message;

    std::string xml;
    xml.append("<message>");
        xml.append("<id>93120f46-a11d-11ea-960a-d46a6af0899d</id>");
        xml.append("<attributes>");
            xml.append("<to>Dean Macfarlane</to>");
            xml.append("<from>Suleman Wynn</from>");
            xml.append("<subject>Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.</subject>");
        xml.append("</attributes>");
    xml.append("<character number=\"92\"></character>");
    xml.append("<body>Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.</body>\"");
    xml.append("</message>");

    std::map<std::string, std::string> attributes {
            {"to", "Dean Macfarlane"},
            {"from", "Suleman Wynn"},
            {"subject", "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit."}
        };

    std::string content = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit.";

    auto parser  = std::make_unique<XMLMessageParser>();
    auto message = parser->fromXml(xml);

    ASSERT_FALSE(message->error());
    ASSERT_EQ(message->body(), content);
    ASSERT_EQ(message->size(), content.size());
    ASSERT_EQ(message->attributes().size(), attributes.size());

    // It prints the XML payload for visualization.
    std::cout << std::endl << message->toXml() << std::endl;

}
