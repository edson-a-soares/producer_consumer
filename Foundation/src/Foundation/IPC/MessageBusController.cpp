#include <memory>
#include "Poco/Exception.h"
#include "Foundation/IPC/BoundedBuffer.h"
#include "Foundation/IPC/BufferChannel.h"
#include "Foundation/IPC/MessageBusController.h"

namespace Foundation {
namespace IPC {


    void MessageBusController::destroyMessageBus()
    {
        BoundedBuffer inputChannel(BufferChannel::INPUT_CHANNEL);
        BoundedBuffer outputChannel(BufferChannel::OUTPUT_CHANNEL);

        inputChannel.clear();
        outputChannel.clear();

        inputChannel.destroy();
        outputChannel.destroy();
    }

    std::shared_ptr<MessageBus> MessageBusController::createMessageBus()
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
