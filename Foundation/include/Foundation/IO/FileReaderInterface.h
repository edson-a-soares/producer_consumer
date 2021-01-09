#ifndef Foundation_IO_FileReaderInterface_INCLUDED
#define Foundation_IO_FileReaderInterface_INCLUDED

#include <string>
#include "Foundation/Foundation.h"

namespace Foundation {
namespace IO {


    class API FileReaderInterface
    {
    public:
        virtual ~FileReaderInterface()= default;
        virtual std::string read() = 0;

    };


} }

#endif
