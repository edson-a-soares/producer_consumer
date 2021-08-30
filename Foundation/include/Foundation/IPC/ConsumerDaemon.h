#ifndef Foundation_IPC_CustomerDaemon_INCLUDED
#define Foundation_IPC_CustomerDaemon_INCLUDED

#include <memory>
#include <string>
#include "Foundation/Foundation.h"
#include "Foundation/IPC/MessageBusChannelInterface.h"

namespace Foundation {
namespace IPC {


    /**
     * A daemon (or service) is a background process that is designed to runOn autonomously, with little or no user
     * intervention. This class executes a handler function that keeps listening to the specified message bus.
     *
     * @see DaemonLoop
     */
    class API ConsumerDaemon {
    public:
        /**
         * It checks if the daemon is listening.
         *
         * @return The status (true or false) value.
         */
        static bool isListening();

        /**
         * It stops the listening.
         */
        static void stopListening();

        /**
         * It starts the listening.
         *
         * @param messageBusInformation The information of the message bus the daemon should be listening to.
         * @param callback The listening function designated to handle the response messages.
         */
        static void startListening(
            std::unique_ptr<MessageBusChannelInterface> messageBusInformation,
            const std::function<std::string (const std::string & message)> & callback);

    };


} }

#endif
