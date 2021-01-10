#ifndef Foundation_IPC_DaemonLoop_INCLUDED
#define Foundation_IPC_DaemonLoop_INCLUDED

#include <string>
#include <thread>
#include <functional>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API DaemonLoop
    {
    public:
        ~DaemonLoop() = default;
        DaemonLoop(DaemonLoop &&) = default;                  // Move constructor
        DaemonLoop(DaemonLoop const &) = delete;              // Copy constructor
        DaemonLoop & operator=(DaemonLoop &&) = delete;       // Move assign
        DaemonLoop & operator=(DaemonLoop const &) = delete;  // Copy assign

        void turnOff();
        bool isRunning() const;
        static DaemonLoop & instance();
        void runWith(const std::function<void()> & worker);

    private:

        DaemonLoop();
        bool loopOn {false};
        std::thread backgroundRunner;

    };


} }

#endif
