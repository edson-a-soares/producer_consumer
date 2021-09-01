#ifndef Foundation_IO_AbstractXmlMessage_INCLUDED
#define Foundation_IO_AbstractXmlMessage_INCLUDED

#include <map>
#include <string>
#include "Poco/DOM/Node.h"
#include "Poco/DOM/DOMParser.h"
#include "Foundation/IO/AbstractFileReader.h"

namespace Foundation {
namespace Message {


    class AbstractXmlMessage : public IO::AbstractFileReader
    {
    public:
        AbstractXmlMessage() = delete;
        ~AbstractXmlMessage() override = default;
        explicit AbstractXmlMessage(const std::string & xmlTemplateFileName);
        void id(const std::string &);

    protected:
        static std::string eraseFormatting(const std::string &);
        std::string buildXML(const std::string & rootElement = "message");
        void set(const std::string & parent, const std::string & tagName, const std::string & value);
        void set(const std::string & tagName, const std::map<std::string, std::string> & attributes);
        void attributeValue(const std::string & tagName, const std::string & attributeName, const std::string & attributeValue);

    private:
        std::string _id;
        Poco::XML::Document * document;

        void replace(const std::string & parentTagName, Poco::XML::Node * oldChild, Poco::XML::Node * newChild);

    };


} }

#endif
