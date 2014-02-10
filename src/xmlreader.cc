// xmlreader.cc
// Implementation of the reader
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "xmlreader.h"

XML_Element::XML_Element(XML_Element* parent_) : name(""),
                        value(""), parent(parent_)
{
}

XML_Element::~XML_Element() {
    if (!elements.empty()) {
        if (elements.back() != nullptr) {
            delete elements.back();
            elements.back() = nullptr;
        }
        elements.pop_back();
    }
    if (!attributes.empty()) {
        if (attributes.back() != nullptr) {
            delete attributes.back();
            attributes.back() = nullptr;
        }
        attributes.pop_back();
    }
}

XMLReader::XMLReader() : root_(nullptr) {
}

XMLReader::~XMLReader() {
    if (root_ != nullptr) {
        delete root_;
        root_ = nullptr;
    }
}

bool XMLReader::open(const std::string &filename)
{
    if (root_ != nullptr) return true;
    
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) return true;
    
    root_ = new XML_Element(nullptr);
    root_->name = "ROOT";
    root_->value = "";
    current_ = root_;
        
    while (file.good()) {
        if (file.peek() == '<') {
            root_->elements.push_back(createElement(file, root_));
        }
        file.get();
    }
    
    file.close();
    
    return false;
}

bool XMLReader::closeElement() {
    if (current_ == nullptr || current_->parent == nullptr) return true;
    
    current_ = current_->parent;
    return false;
}

bool XMLReader::close() {
    if (root_ != nullptr) {
        delete root_;
        root_ = nullptr;
        current_ = nullptr;
        return false;
    }
    return true;
}

bool XMLReader::readElement(const std::string &name, unsigned int number) {
    if (current_ == nullptr) return true;
    
    for (unsigned int i = 0; i < current_->elements.size(); ++i) {
        if (current_->elements[i]->name == name) {
            if (number < 1) {
                current_ = current_->elements[i];
                return false;
            }
            --number;
        }
    }
    
    return true;
}

std::string XMLReader::getAttributeValue(const std::string &name) const {
    if (current_ != nullptr) {
        for (unsigned int i = 0; i < current_->attributes.size(); ++i) {
            if (current_->attributes[i]->name == name) {
                return current_->attributes[i]->value;
            }
        }
    }
    return std::string();
}

std::string XMLReader::getElementValue() const {
    if (current_ == nullptr) {
        return std::string();
    }
    
    return current_->value;
}

XML_Attribute* XMLReader::createAttribute(std::ifstream &stream) {
    std::string name;
    std::string value;
    
    while (stream.peek() != '=') {
        name += stream.get();
    }
    stream.get();
    if (stream.peek() == '"') {
        stream.get();
        while (stream.peek() != '"') {
            value += stream.get();
        }
    }
    else if (stream.peek() == '\'') {
        stream.get();
        while (stream.peek() != '\'') {
            value += stream.get();
        }
    }
    
    stream.get();
        
    return new XML_Attribute{name,value};
}

XML_Element* XMLReader::createElement(std::ifstream &stream, XML_Element* parent) {

    while (stream.good() && stream.peek() != '<') {
        stream.get();
    }
    if (!stream.good()) return nullptr;
    
    XML_Element* ele = new XML_Element(parent);
    if (stream.peek() == '<') {
        stream.get();
        while (stream.peek() != '>' && stream.peek() != ' '  && stream.peek() != '/') {
            ele->name += stream.get();
        }
        while (stream.peek() == ' ') {
            stream.get();
            if (!(stream.peek() == ' ' || stream.peek() == '/' || stream.peek() == '>')) {
                ele->attributes.push_back(createAttribute(stream));
            }
        }
        if (stream.peek() == '/') {
            ele->value = "";
            stream.get();
            stream.get();
            return ele;
        }
        stream.get();
    }
    if (stream.peek() == '/') {
        ele->value = "";
        stream.get();
        stream.get();
        return ele;
    }
    while (stream.peek() != '<') {
        ele->value += stream.get();
    }
    while (true) {
        if (stream.peek() == '<')
        {
            int pos = stream.tellg();
            bool good = true;
            stream.get();
            if (stream.get() != '/') {
                stream.seekg(pos);
                ele->elements.push_back(createElement(stream, ele));
                good = false;;
            }
            if (good) {
                for (unsigned int i = 0; i < ele->name.length(); ++i) {
                    if (stream.get() != ele->name[i]) {
                        stream.seekg(pos);
                        ele->elements.push_back(createElement(stream, ele));
                        good = false;
                        break;
                    }
                }
            }
            if (good) {
                break;
            }
        }
        else {
            stream.get();
        }
    }
    return ele;
}

