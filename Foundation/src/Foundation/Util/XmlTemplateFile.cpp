#include "Poco/Logger.h"
#include "Poco/Exception.h"
#include "Foundation/Util/Path.h"
#include "Foundation/Util/XmlTemplateFile.h"

namespace Foundation {
namespace Util {


    std::string XmlFileTemplate::file(const std::string & fileName)
    {
        std::string filePath;
        try {
            filePath = Path::APPLICATION_HOME_DIRECTORY_PATH;
            filePath.append("/data/templates/")
                .append(fileName)
                .append(".xml");

            if ( filePath.empty() )
                throw Poco::Exception("", " ", 0);

        } catch (Poco::NotFoundException & exception) {

            Poco::Logger & logger = Poco::Logger::get("TestLogger");
            logger.information(exception.message());

            throw;
        }

        return filePath;
    }


} }
