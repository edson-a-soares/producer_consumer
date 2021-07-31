#ifndef Foundation_IPC_MessageBus_INCLUDED
#define Foundation_IPC_MessageBus_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/DaemonLoop.h"
#include "Foundation/IPC/BoundedBuffer.h"

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
         * A constructor.
         *
         * @param inputChannel
         * @param outputChannel
         */
        MessageBus(std::unique_ptr<BoundedBuffer> inputChannel, std::unique_ptr<BoundedBuffer> outputChannel);

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

    private:
        std::unique_ptr<BoundedBuffer> inputChannel;
        std::unique_ptr<BoundedBuffer> outputChannel;

        void destroyChannels();

    };


} }

#endif
