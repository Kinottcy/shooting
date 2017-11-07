//
//  XmlDocument.hpp
//  Game Framework
//
//  Created by numata on July 01, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __XML_DOCUMENT_HPP__
#define __XML_DOCUMENT_HPP__

#include "GMObject.hpp"
#include "GameError.hpp"
#include <string>
#include "tinyxml2.h"


class XmlDocument : public GMObject
{
    std::string             mFileName;
    tinyxml2::XMLDocument   xmlDoc;
    tinyxml2::XMLElement    *xmlElem;

    bool    isAtEnd;

public:
    static XmlDocument Parse(const std::string& str) throw(GameError);

private:
    XmlDocument(int dummy, const std::string& str) throw(GameError);

public:
    XmlDocument(const std::string& filename) throw(GameError);
    XmlDocument(const XmlDocument& doc);
    ~XmlDocument();

public:
    std::string GetAttribute(const std::string& attrName) const;
    bool        GetBoolAttribute(const std::string& attrName) const;
    std::string GetChildAttribute(const std::string& childName, const std::string& attrName);
    bool        GetChildBoolAttribute(const std::string& childName, const std::string& attrName) const;
    float       GetChildFloatAttribute(const std::string& childName, const std::string& attrName) const;
    int         GetChildIntAttribute(const std::string& childName, const std::string& attrName) const;
    std::string GetChildText(const std::string& childName) const;
    std::string GetFileName() const;
    float       GetFloatAttribute(const std::string& attrName) const;
    int         GetIntAttribute(const std::string& attrName) const;
    std::string GetName() const;
    std::string GetText() const;

    bool        HasAttribute(const std::string& attrName) const;
    bool        HasChild() const;
    bool        HasChild(const std::string& childName) const;
    bool        HasChildAttribute(const std::string& childName, const std::string& attrName) const;

    bool        IsAtEnd() const;
    bool        MoveToFirstChild();
    bool        MoveToNextSibling();
    bool        MoveToParent();

    std::string ToString() const override;

};


#endif  //#ifndef __XML_DOCUMENT_HPP__

