#ifndef Foundation_IPC_MessageBusChannelInterface_INCLUDED
#define Foundation_IPC_MessageBusChannelInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API MessageBusChannelInterface
    {
    public:
        virtual ~MessageBusChannelInterface() = default;
        virtual int length() = 0;
        virtual std::string inputName() = 0;
        virtual std::string outputName() = 0;

    };


} }

#endif
