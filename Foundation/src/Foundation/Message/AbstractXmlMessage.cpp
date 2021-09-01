#include <regex>
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/UUIDGenerator.h"
#include "Foundation/Util/XmlTemplateFile.h"
#include "Foundation/Message/AbstractXmlMessage.h"

namespace Foundation {
namespace Message {


    AbstractXmlMessage::AbstractXmlMessage(const std::string & xmlTemplateFileName)
        : AbstractFileReader(Util::XmlFileTemplate::file(xmlTemplateFileName)),
          _id(),
          document(nullptr)
    {
        Poco::XML::DOMParser parser;
        document = parser.parseString(read());

        Poco::UUIDGenerator & generator = Poco::UUIDGenerator::defaultGenerator();
        Poco::UUID uuid(generator.create());
        _id = uuid.toString();
    }

    std::string AbstractXmlMessage::buildXML(const std::string & rootElement)
    {
        std::stringstream buffer;
        Poco::XML::DOMWriter writer;

        set(rootElement, "id", _id);

        writer.setOptions(Poco::XML::XMLWriter::CANONICAL_XML);
        writer.writeNode(buffer, document);
        return buffer.str();
    }

    std::string AbstractXmlMessage::eraseFormatting(const std::string & content)
    {
        std::regex expression(">[\\s\r\n]*<");
        return std::regex_replace(content, expression, "><");
    }

    void AbstractXmlMessage::set(const std::string & parent, const std::string & tagName, const std::string & value)
    {
        auto newChild = document->createElement(tagName);
        newChild->appendChild(reinterpret_cast<Poco::XML::Node *>(document->createTextNode(value)));

        replace(parent, document->getElementsByTagName(tagName)->item(0), newChild);
    }

    void AbstractXmlMessage::attributeValue(const std::string & tagName,
                                            const std::string & attributeName,
                                            const std::string & attributeValue)
    {
        auto element = document->createElement(tagName);
        element->setAttribute(attributeName, attributeValue);

        auto oldChild = document->getElementsByTagName(tagName);
        replace(oldChild->item(0)->parentNode()->nodeName(), oldChild->item(0), element);
    }

    void AbstractXmlMessage::set(const std::string & tagName, const std::map<std::string, std::string> & attributes)
    {
        auto element = document->createElement(tagName);

        for (auto const & attr : attributes) {
            auto newAttribute = document->createAttribute(attr.first);
            element->setAttributeNode(newAttribute);
            element->setAttribute(attr.first, attr.second);
        }

        auto oldChild = document->getElementsByTagName(tagName);
        replace(oldChild->item(0)->parentNode()->nodeName(), oldChild->item(0), element);
    }

    void AbstractXmlMessage::id(const std::string & id)
    {
        _id = id;
    }

    void AbstractXmlMessage::replace(const std::string & parentTagName, Poco::XML::Node * oldChild, Poco::XML::Node * newChild)
    {
        auto parentElement = document->getElementsByTagName(parentTagName);
        if (parentElement->length() == 0)
            return;

        parentElement->item(0)->replaceChild(newChild, oldChild)->release();
    }


} }
