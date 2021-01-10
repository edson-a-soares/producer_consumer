#include "gtest/gtest.h"
#include "Poco/Exception.h"
#include "IPC/Double/FakeSimpleBuffer.h"

TEST(SimpleBufferTest, AttemptToCreateOrOpenBufferWithInvalidParams)
{
    using namespace Double;

    ASSERT_THROW(FakeSimpleBuffer invalidNameBuffer(""), Poco::InvalidArgumentException);
    ASSERT_THROW(FakeSimpleBuffer invalidNameBuffer("", 512), Poco::InvalidArgumentException);
    ASSERT_THROW(
            FakeSimpleBuffer invalidSizeBuffer("__TESTING_BUFFER__", 0),
            Poco::InvalidArgumentException
        );

}

TEST(SimpleBufferTest, AttemptToOpenNonExistentBuffer)
{
    using namespace Double;

    ASSERT_THROW(
            FakeSimpleBuffer nonExistentBuffer("__TESTING_BUFFER__"),
            Poco::FileNotFoundException
        );

}

TEST(SimpleBufferTest, AttemptToCreateAlreadyExistentBuffer)
{
    using namespace Double;

    FakeSimpleBuffer newBuffer("__TESTING_BUFFER__", 512);
    ASSERT_THROW(
            FakeSimpleBuffer existentBuffer("__TESTING_BUFFER__", 512),
            Poco::FileExistsException
        );

    ASSERT_TRUE(newBuffer.exists());
    ASSERT_TRUE(newBuffer.empty());
    ASSERT_NO_THROW(newBuffer.destroy());

}

TEST(SimpleBufferTest, CheckIfBufferIsEmpty)
{
    using namespace Double;

    FakeSimpleBuffer temporaryBuffer("__TESTING_BUFFER__", 512);
    ASSERT_TRUE(temporaryBuffer.exists());
    ASSERT_TRUE(temporaryBuffer.empty());

    ASSERT_NO_THROW(temporaryBuffer.put("anything"));
    ASSERT_FALSE(temporaryBuffer.empty());
    ASSERT_NO_THROW(temporaryBuffer.destroy());

}

TEST(SimpleBufferTest, CheckIfBufferIsClean)
{
    using namespace Double;

    FakeSimpleBuffer temporaryBuffer("__TESTING_BUFFER__", 512);
    ASSERT_TRUE(temporaryBuffer.exists());

    ASSERT_TRUE(temporaryBuffer.empty());
    ASSERT_NO_THROW(temporaryBuffer.put("anything"));
    ASSERT_FALSE(temporaryBuffer.empty());
    ASSERT_NO_THROW(temporaryBuffer.clear());
    ASSERT_TRUE(temporaryBuffer.empty());
    ASSERT_NO_THROW(temporaryBuffer.destroy());

}

TEST(SimpleBufferTest, SingleProcessBufferContentExchange)
{
    using namespace Double;

    auto content = "anything ...";
    FakeSimpleBuffer singleProcessBuffer("__PRODUCER_CONSUMER_BUFFER__", 512);

    ASSERT_TRUE(singleProcessBuffer.exists());
    ASSERT_TRUE(singleProcessBuffer.empty());
    ASSERT_NO_THROW(singleProcessBuffer.put(content));
    ASSERT_EQ(singleProcessBuffer.get(), content);
    ASSERT_TRUE(singleProcessBuffer.empty());
    ASSERT_NO_THROW(singleProcessBuffer.destroy());

}
