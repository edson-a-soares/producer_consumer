#include <string>
#include <unistd.h>
#include "gtest/gtest.h"
#include "Poco/Exception.h"
#include "Foundation/IPC/BoundedBuffer.h"

TEST(BoundedBufferTest, AttemptToCreateAlreadyExistentBuffer)
{
    using namespace Foundation::IPC;

    auto bufferName = "__TESTING_BUFFER__";
    ASSERT_NO_THROW(BoundedBuffer firstBuffer(bufferName, 512));
    ASSERT_THROW(
            BoundedBuffer secondBuffer(bufferName, 512),
            Poco::FileExistsException
        );

    BoundedBuffer lastBuffer(bufferName);
    ASSERT_NO_THROW(lastBuffer.destroy());

}

TEST(BoundedBufferTest, SingleProcessSuccessfulContentExchange)
{
    using namespace Foundation::IPC;

    auto content = "Content into buffer.";
    auto bufferName = "__TESTING_BUFFER__";
    BoundedBuffer createBuffer(bufferName, 1024);

    BoundedBuffer openBuffer(bufferName);
    ASSERT_NO_THROW(openBuffer.put(content));
    ASSERT_EQ(openBuffer.get(), content);
    ASSERT_NO_THROW(openBuffer.destroy());

}

TEST(BoundedBufferTest, SingleProcessMultipleSuccessfulContentExchange)
{
    using namespace Foundation::IPC;

    auto content = "Content into buffer.";
    auto bufferName = "__TESTING_BUFFER__";
    BoundedBuffer createBuffer(bufferName, 1024);

    BoundedBuffer openBuffer(bufferName);
    for ( int i = 0; i < 100; ++i ) {
        ASSERT_NO_THROW(openBuffer.put(content));
        ASSERT_EQ(openBuffer.get(), content);
    }

    ASSERT_NO_THROW(openBuffer.destroy());

}
