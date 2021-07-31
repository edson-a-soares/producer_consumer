#include "Foundation/IPC/DaemonLoop.h"

namespace Foundation {
namespace IPC {


    DaemonLoop & DaemonLoop::instance()
    {
        static DaemonLoop instance;
        return instance;
    }

    void DaemonLoop::turnOff()
    {
        loopOn = false;
        backgroundRunner.join();
    }

    bool DaemonLoop::isRunning() const
    {
        return loopOn;
    }

    void DaemonLoop::runWith(const std::function<void ()> & worker)
    {
        if (loopOn)
            return;

        loopOn = true;
        backgroundRunner = std::thread([=](){
            do {
                if (worker)
                    worker();

            } while (loopOn);
        });
    }


} }
