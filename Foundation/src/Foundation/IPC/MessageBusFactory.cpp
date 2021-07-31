#include <memory>
#include "Poco/Exception.h"
#include "Foundation/IPC/BoundedBuffer.h"
#include "Foundation/IPC/MessageBusFactory.h"

namespace Foundation {
namespace IPC {


    std::shared_ptr<MessageBus> MessageBusFactory::getMessageBus(std::unique_ptr<MessageBusInformationInterface> information)
    {
        std::unique_ptr<BoundedBuffer> input  = nullptr;
        std::unique_ptr<BoundedBuffer> output = nullptr;

        try {
            input  = std::make_unique<BoundedBuffer>(information->inputChannelName());
            output = std::make_unique<BoundedBuffer>(information->outputChannelName());

        } catch (Poco::FileNotFoundException &) {
            input  = std::make_unique<BoundedBuffer>(information->inputChannelName(), information->channelsLength());
            output = std::make_unique<BoundedBuffer>(information->outputChannelName(), information->channelsLength());

        }

        return std::make_shared<MessageBus>(std::move(input), std::move(output));
    }


} }
