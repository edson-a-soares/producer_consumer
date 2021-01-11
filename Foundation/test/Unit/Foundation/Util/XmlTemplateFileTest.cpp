#include <string>
#include <gtest/gtest.h>
#include "Poco/Exception.h"
#include "boost/filesystem.hpp"
#include "Foundation/Util/XmlTemplateFile.h"

TEST(XmlTemplateFileTest, FileNotFoundException)
{
    using namespace Foundation::Util;

    ASSERT_THROW(XmlFileTemplate::file("path/to/non-file.xml"),
        Poco::FileNotFoundException
    );

}

TEST(XmlTemplateFileTest, FindTemplate)
{
    using namespace Foundation::Util;

    auto templateFile = XmlFileTemplate::file("message");
    ASSERT_TRUE(boost::filesystem::exists(templateFile));

}
