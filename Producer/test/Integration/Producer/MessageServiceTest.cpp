#include <string>
#include "Poco/Path.h"
#include "gtest/gtest.h"
#include "Foundation/System/Console.h"
#include "Foundation/System/Application.h"

class MessageServiceTest : public ::testing::Test
{
public:
    MessageServiceTest() = default;
    ~MessageServiceTest() override = default;

protected:
    void SetUp() final
    {}

    void TearDown() final
    {}

};


TEST_F(MessageServiceTest, InterprocessExchangeContentWithSuccess)
{
    ASSERT_TRUE(true);
}

