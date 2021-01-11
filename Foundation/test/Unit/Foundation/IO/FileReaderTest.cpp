#include <string>
#include <gtest/gtest.h>
#include "Poco/Exception.h"
#include "Foundation/IO/AbstractFileReader.h"


class InnerFileReader : public Foundation::IO::AbstractFileReader
{
public:
    explicit InnerFileReader(std::string filePath);

};

InnerFileReader::InnerFileReader(std::string filePath)
    : Foundation::IO::AbstractFileReader(std::move(filePath))
{}


TEST(FileReaderTest, FileNotFoundException)
{
    using namespace Foundation::IO;

    auto fileReader = std::make_unique<InnerFileReader>("non-file.xml");
    ASSERT_THROW(fileReader->read(), Poco::FileNotFoundException);

}

