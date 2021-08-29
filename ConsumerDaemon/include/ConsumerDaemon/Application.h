#ifndef ConsumerDaemon_Application_INCLUDED
#define ConsumerDaemon_Application_INCLUDED

#include "Foundation/Foundation.h"

namespace ConsumerDaemon {


    class API Application {
    public:
        static void run(int option = 0, bool keepAlive = true);

    };


}

#endif
