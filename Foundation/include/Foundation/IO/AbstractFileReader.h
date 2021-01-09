#ifndef Foundation_IO_AbstractFileReader_INCLUDED
#define Foundation_IO_AbstractFileReader_INCLUDED

#include <string>
#include "Poco/File.h"
#include "Foundation/Foundation.h"
#include "Foundation/IO/FileReaderInterface.h"

namespace Foundation {
namespace IO {


    class API AbstractFileReader : public FileReaderInterface
    {
    public:
        AbstractFileReader() = delete;
        explicit AbstractFileReader(std::string filePath);
        ~AbstractFileReader() override = default;
        std::string read() final;

    private:
        std::string _filePath;

    };


} }

#endif
