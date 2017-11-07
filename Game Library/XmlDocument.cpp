//
//  XmlDocument.cpp
//  Game Framework
//
//  Created by numata on July 01, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "XmlDocument.hpp"
#include "tinyxml2_util.hpp"
#include "StringSupport.hpp"
#include "Globals.hpp"


XmlDocument XmlDocument::Parse(const std::string& str) throw(GameError)
{
    return XmlDocument(0, str);
}

XmlDocument::XmlDocument(int dummy, const std::string& str) throw(GameError)
{
    __gGMLastErrorPlace = "XmlDocument::XmlDocument()";
    try {
        XMLParseString(xmlDoc, str);
        xmlElem = xmlDoc.RootElement();
        isAtEnd = false;
    } catch (std::exception& e) {
        throw GameError(e.what());
    }
}

XmlDocument::XmlDocument(const std::string& filename) throw(GameError)
{
    __gGMLastErrorPlace = "XmlDocument::XmlDocument()";
    mFileName = filename;
    try {
        XMLLoadResourceFile(xmlDoc, filename);
        xmlElem = xmlDoc.RootElement();
        isAtEnd = false;
    } catch (std::exception& e) {
        throw GameError(e.what());
    }
}

XmlDocument::XmlDocument(const XmlDocument& doc)
{
    // Do nothing
}

XmlDocument::~XmlDocument()
{
    // Do nothing
}

std::string XmlDocument::GetName() const
{
    if (isAtEnd) {
        return "";
    }
    return xmlElem->Name();
}

std::string XmlDocument::GetText() const
{
    if (isAtEnd) {
        return "";
    }
    return xmlElem->GetText();
}

std::string XmlDocument::GetAttribute(const std::string& attrName) const
{
    if (isAtEnd) {
        return "";
    }
    return xmlElem->Attribute(attrName.c_str());
}

bool XmlDocument::GetBoolAttribute(const std::string& attrName) const
{
    if (isAtEnd) {
        return false;
    }
    return xmlElem->BoolAttribute(attrName.c_str());
}

float XmlDocument::GetFloatAttribute(const std::string& attrName) const
{
    if (isAtEnd) {
        return 0.0f;
    }
    return xmlElem->FloatAttribute(attrName.c_str());
}

std::string XmlDocument::GetFileName() const
{
    return mFileName;
}

int XmlDocument::GetIntAttribute(const std::string& attrName) const
{
    if (isAtEnd) {
        return 0;
    }
    return xmlElem->IntAttribute(attrName.c_str());
}

bool XmlDocument::HasAttribute(const std::string& attrName) const
{
    if (isAtEnd) {
        return false;
    }
    return (xmlElem->Attribute(attrName.c_str()) != 0);
}

bool XmlDocument::HasChild() const
{
    if (isAtEnd) {
        return false;
    }
    return (xmlElem->FirstChildElement() != 0);
}

static tinyxml2::XMLElement *FindChildElement(tinyxml2::XMLElement *elem, const std::string& childName)
{
    tinyxml2::XMLElement *child = elem->FirstChildElement();
    while (child) {
        std::string aChildName = child->Name();
        if (aChildName == childName) {
            return child;
        }
        child = child->NextSiblingElement();
    }
    return 0;
}

bool XmlDocument::HasChild(const std::string& childName) const
{
    if (isAtEnd) {
        return false;
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    return (child != 0);
}

std::string XmlDocument::GetChildText(const std::string& childName) const
{
    if (isAtEnd) {
        return "";
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return "";
    }
    return child->GetText();
}

std::string XmlDocument::GetChildAttribute(const std::string& childName, const std::string& attrName)
{
    if (isAtEnd) {
        return "";
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return "";
    }
    return child->Attribute(attrName.c_str());
}

bool XmlDocument::GetChildBoolAttribute(const std::string& childName, const std::string& attrName) const
{
    if (isAtEnd) {
        return false;
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return false;
    }
    return child->BoolAttribute(attrName.c_str());
}

float XmlDocument::GetChildFloatAttribute(const std::string& childName, const std::string& attrName) const
{
    if (isAtEnd) {
        return 0.0f;
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return 0.0f;
    }
    return child->FloatAttribute(attrName.c_str());
}

int XmlDocument::GetChildIntAttribute(const std::string& childName, const std::string& attrName) const
{
    if (isAtEnd) {
        return 0;
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return 0;
    }
    return child->IntAttribute(attrName.c_str());
}

bool XmlDocument::HasChildAttribute(const std::string& childName, const std::string& attrName) const
{
    if (isAtEnd) {
        return false;
    }
    tinyxml2::XMLElement *child = FindChildElement(xmlElem, childName);
    if (!child) {
        return false;
    }
    return (child->Attribute(attrName.c_str()) != 0);
}

bool XmlDocument::MoveToFirstChild()
{
    if (isAtEnd) {
        return false;
    }
    tinyxml2::XMLElement *child = xmlElem->FirstChildElement();
    if (!child) {
        return false;
    }
    xmlElem = child;
    return true;
}

bool XmlDocument::MoveToNextSibling()
{
    if (isAtEnd) {
        return false;
    }
    tinyxml2::XMLElement *next = xmlElem->NextSiblingElement();
    if (!next) {
        isAtEnd = true;
        return false;
    }
    xmlElem = next;
    return true;
}

bool XmlDocument::MoveToParent()
{
    tinyxml2::XMLNode *parentNode = xmlElem->Parent();
    if (!parentNode) {
        return false;
    }
    tinyxml2::XMLElement *parentElem = parentNode->ToElement();
    if (!parentElem) {
        return false;
    }
    isAtEnd = false;
    xmlElem = parentElem;
    return true;
}

bool XmlDocument::IsAtEnd() const
{
    return isAtEnd;
}

std::string XmlDocument::ToString() const
{
    return FormatString("XmlDocument(%s)", mFileName.c_str());
}


