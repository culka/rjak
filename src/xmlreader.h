// xmlreader.h
// Reads unit info from xml
// Why? Because it's easy to validate and read
// Teemu Mäkinen <culkah@gmail.com> 2014

#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <string>
#include <vector>
#include <fstream>

struct XML_Attribute {
    std::string name;
    std::string value;
};

// Elements that maintain the structure properly
struct XML_Element {
    XML_Element(XML_Element* parent_);
    ~XML_Element();
    std::string name;
    std::string value;
    XML_Element* parent;
    std::vector<XML_Element*> elements;
    std::vector<XML_Attribute*> attributes;
};

class XMLReader {
 public:
    XMLReader();
    ~XMLReader();
    
    // Open a specified file, return false on success, and true on error
    bool open(const std::string &filename);
    // Closes an opened file structure
    bool close();
    
    // Opens element from current parent, starts from root
    bool readElement(const std::string &name, unsigned int number = 0);
    // Goes upward one element from current one
    bool closeElement();
    // Gets the value of the element of given name
    std::string getAttributeValue(const std::string &name) const;
    // Gets the value of the currently open element
    std::string getElementValue() const;
    

 private:
    
    XML_Element* root_;
    XML_Element* current_;
    
    XML_Element* createElement(std::ifstream &stream, XML_Element* parent);
    XML_Attribute* createAttribute(std::ifstream &stream);
};

#endif
