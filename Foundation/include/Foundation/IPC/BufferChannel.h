#ifndef Foundation_IPC_BufferChannel_INCLUDED
#define Foundation_IPC_BufferChannel_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API BufferChannel
    {
    public:
        static const int CHANNEL_LENGTH;
        static const std::string INPUT_CHANNEL;
        static const std::string OUTPUT_CHANNEL;

    };


} }

#endif
