#include <fstream>
#include <sstream>
#include "Poco/Exception.h"
#include "Poco/Environment.h"
#include "Foundation/IO/AbstractFileReader.h"

namespace Foundation {
namespace IO {


    AbstractFileReader::AbstractFileReader(std::string filePath)
        : _filePath(std::move(filePath))
    {}

    std::string AbstractFileReader::read()
    {
	    Poco::File configurationFile = Poco::File(_filePath);
        if ( !configurationFile.exists() )
            throw Poco::FileNotFoundException("File Not Found", " File " + _filePath + " does not exists.");

        std::stringstream buffer;
        std::ifstream fileStream(configurationFile.path().c_str());

        buffer << fileStream.rdbuf();
        std::string fileContent = buffer.str();

        return fileContent;
    }


} }
