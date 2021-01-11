#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/Exception.h"
#include "Foundation/Util/Path.h"
#include "Foundation/Util/XmlTemplateFile.h"

namespace Foundation {
namespace Util {


    std::string XmlFileTemplate::file(const std::string & fileName)
    {
        std::string filePath = Path::APPLICATION_HOME_DIRECTORY_PATH;
        filePath.append("/data/templates/")
            .append(fileName)
            .append(".xml");

        Poco::File templateFile = Poco::File(filePath);
        if ( !templateFile.exists() || !templateFile.isFile() )
            throw Poco::FileNotFoundException("File Not Found", " File " + filePath + " does not exists.");

        return filePath;
    }


} }
