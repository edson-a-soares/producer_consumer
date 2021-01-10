#ifndef Foundation_IPC_CustomerDaemon_INCLUDED
#define Foundation_IPC_CustomerDaemon_INCLUDED

#include <memory>
#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API ConsumerDaemon {
    public:
        static bool isMonitoring();
        static void stopMonitoring();
        static void startMonitoring(const std::function<std::string (const std::string & message)> & callback);

    };


} }

#endif
