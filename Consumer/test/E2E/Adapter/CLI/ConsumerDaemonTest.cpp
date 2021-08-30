#include <string>
#include "gtest/gtest.h"

class ConsumerDaemonTest : public ::testing::Test
{
public:
    ConsumerDaemonTest() = default;
    ~ConsumerDaemonTest() override = default;

protected:
    void SetUp() final
    {}

    void TearDown() final
    {}

};


TEST_F(ConsumerDaemonTest, StatusNotRunning)
{
    ASSERT_TRUE(true);
}

TEST_F(ConsumerDaemonTest, StatusRunning)
{
    ASSERT_TRUE(true);
}
