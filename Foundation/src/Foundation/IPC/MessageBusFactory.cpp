#include <memory>
#include "Poco/Exception.h"
#include "Foundation/IPC/BoundedBuffer.h"
#include "Foundation/IPC/BufferChannel.h"
#include "Foundation/IPC/MessageBusFactory.h"

namespace Foundation {
namespace IPC {


    std::shared_ptr<MessageBus> MessageBusFactory::createMessageBus()
    {
        std::unique_ptr<BoundedBuffer> input  = nullptr;
        std::unique_ptr<BoundedBuffer> output = nullptr;

        try {
            input  = std::make_unique<BoundedBuffer>(BufferChannel::INPUT_CHANNEL);
            output = std::make_unique<BoundedBuffer>(BufferChannel::OUTPUT_CHANNEL);

        } catch (Poco::FileNotFoundException &) {
            input  = std::make_unique<BoundedBuffer>(BufferChannel::INPUT_CHANNEL, BufferChannel::CHANNEL_LENGTH);
            output = std::make_unique<BoundedBuffer>(BufferChannel::OUTPUT_CHANNEL, BufferChannel::CHANNEL_LENGTH);

        }

        return std::make_shared<MessageBus>(std::move(input), std::move(output));
    }


} }
