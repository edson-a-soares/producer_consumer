#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "Poco/Exception.h"
#include "Adapter/Http/DefaultXMLErrorMessage.h"

TEST(XMLErrorMessageTest, toXml)
{
    auto errorMessage = std::make_unique<::Http::DefaultXMLErrorMessage>(
        "Bad Request",
        "400",
        "Client sent an invalid request, such as lacking required request body or parameter",
        "1a208788-0aae-11ec-83fe-d46a6af0899d"
    );

    auto errorString =
        "<error>"
             "<id>1a208788-0aae-11ec-83fe-d46a6af0899d</id>"
             "<type>Bad Request</type>"
             "<status>400</status>"
             "<detail>Client sent an invalid request, such as lacking required request body or parameter</detail>"
         "</error>";

    ASSERT_EQ(errorMessage->toXml(), errorString);

    // It prints the XML payload for visualization.
    poco_debugger_msg(errorMessage->toXml().c_str());

}
