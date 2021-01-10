#ifndef Foundation_IPC_BufferInterface_INCLUDED
#define Foundation_IPC_BufferInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IPC {


    class API BufferInterface
    {
    public:
        virtual ~BufferInterface() = default;
        virtual void clear() = 0;
        virtual bool empty() = 0;
        virtual bool exists() = 0;
        virtual void destroy() = 0;
        virtual std::string get() = 0;
        virtual void put(const std::string & content) = 0;

    };


} }

#endif
