#ifndef Foundation_IPC_MessageBus_INCLUDED
#define Foundation_IPC_MessageBus_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/BoundedBuffer.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace Foundation {
namespace IPC {


    /**
     * A Message Bus is a combination of a common data model, a common command set, and a messaging infrastructure to
     * allow different systems to communicate through a shared set of interfaces.
     *
     * This class is a mechanism for managing the exchange of messages from sending and receiving (i.e., producers|consumers,
     * senders|listeners) in different processes.
     */
    class API MessageBus {
    public:
        /**
         * A constructor.
         */
        MessageBus() = delete;

        /**
         * A destructor.
         */
        ~MessageBus();

        MessageBus(MessageBus &) = delete;
        MessageBus(MessageBus &&) noexcept = default;

        /**
         * It just gets the response message.
         *
         * @return The response message.
         */
        std::string readResponse();

        /**
         * It just sends a message.
         *
         * @param content The message content to be sent.
         */
        void sendMessage(const std::string & content);

        /**
         * It reads a message with a specific handler function.
         *
         * @param messageHandler The handler function for processing the response message.
         */
        void readMessage(const std::function<std::string (const std::string & message)> & messageHandler) const;

        /**
         * It sends a message and defines a response handler function to process it.
         *
         * @param message The message to send.
         * @param responseHandler The handler function for processing the response message.
         */
        void sendMessage(const std::string & message, const std::function<void (const std::string & response)> & responseHandler);

        /**
         * It destroys the bus channels immediately.
         */
        void destroyChannels();

        /**
         * It creates MessageBus instances.
         *
         * Once the MessageBus constructor is private, this is the only way to do it.
         */
        class Factory {
        public:
            static std::shared_ptr<MessageBus> create(std::unique_ptr<MessageBusChannelInterface>);
            static std::shared_ptr<MessageBus> createClient(std::unique_ptr<MessageBusChannelInterface>);

        private:
            static std::shared_ptr<MessageBus> construct(std::unique_ptr<MessageBusChannelInterface>);

        };

    private:
        bool automaticChannelsManagement;
        std::unique_ptr<BoundedBuffer> inputChannel;
        std::unique_ptr<BoundedBuffer> outputChannel;

        /**
         * A constructor.
         *
         * @param inputChannel
         * @param outputChannel
         */
        MessageBus(std::unique_ptr<BoundedBuffer> inputChannel, std::unique_ptr<BoundedBuffer> outputChannel);

        /**
         * It allows the user to control the lifecycle of the bus channels manually.
         *
         * That is useful when the producer and the consumer are in different processes and, after using the bus, the
         * client do not want to destroy the channels.
         */
        void disableChannelsManagement();

        friend Factory;
    };


} }

#endif
