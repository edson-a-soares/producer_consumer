#ifndef Foundation_IPC_DaemonLoop_INCLUDED
#define Foundation_IPC_DaemonLoop_INCLUDED

#include <string>
#include <thread>
#include <functional>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    /**
     * A daemon (or service) is a background process that is designed to run autonomously, with little or no user
     * intervention. This class executes a function continuously in the background and offers the controls to manage it.
     * This is like a typical loop (i.e., while) but with explicit terminating controls.
     */
    class API DaemonLoop
    {
    public:
        ~DaemonLoop() = default;
        DaemonLoop(DaemonLoop &&) = default;                  // Move constructor
        DaemonLoop(DaemonLoop const &) = delete;              // Copy constructor
        DaemonLoop & operator=(DaemonLoop &&) = delete;       // Move assign
        DaemonLoop & operator=(DaemonLoop const &) = delete;  // Copy assign

        /**
         * It stops the daemon loop.
         */
        void turnOff();

        /**
         * It checks if the daemon loop is running or not.
         *
         * @return The status (true or false) value.
         */
        bool isRunning() const;

        /**
         * It creates a single instance of the daemon loop.
         *
         * @return DaemonLoop
         */
        static DaemonLoop & instance();

        /**
         * It runs the daemon loop with a function until it is explicitly stopped.
         *
         * @param worker The function to execute continuously as a background process.
         */
        void runWith(const std::function<void()> & worker);

    private:
        DaemonLoop() = default;
        bool loopOn {false};
        std::thread backgroundRunner;

    };


} }

#endif
