//
//  tinyxml2_util.mm
//  Game Framework
//
//  Created by numata on July 15, 2014.
//  Copyright (c) 2014-2016 Satoshi Numata. All rights reserved.
//

#include <string>
#import <Foundation/Foundation.h>

#include "tinyxml2_util.hpp"
#include "StringSupport.hpp"


std::string XMLErrorToString(tinyxml2::XMLError err)
{
    using namespace tinyxml2;
    
    if (err == XML_NO_ERROR) {
        return "エラーなし";
    } else if (err == XML_NO_ATTRIBUTE) {
        return "属性が指定されていません";
    } else if (err == XML_WRONG_ATTRIBUTE_TYPE) {
        return "属性のタイプが不正です";
    } else if (err == XML_ERROR_FILE_NOT_FOUND) {
        return "ファイルが見つかりません";
    } else if (err == XML_ERROR_FILE_COULD_NOT_BE_OPENED) {
        return "ファイルが開けません";
    } else if (err == XML_ERROR_FILE_READ_ERROR) {
        return "ファイル読み込みに失敗しました";
    } else if (err == XML_ERROR_ELEMENT_MISMATCH) {
        return "要素のミスマッチです";
    } else if (err == XML_ERROR_PARSING_ELEMENT) {
        return "要素のパースに失敗しました";
    } else if (err == XML_ERROR_PARSING_ATTRIBUTE) {
        return "属性のパースに失敗しました";
    } else if (err == XML_ERROR_IDENTIFYING_TAG) {
        return "タグの特定に失敗しました";
    } else if (err == XML_ERROR_PARSING_TEXT) {
        return "テキストのパースに失敗しました";
    } else if (err == XML_ERROR_PARSING_CDATA) {
        return "CDATAのパースに失敗しました";
    } else if (err == XML_ERROR_PARSING_COMMENT) {
        return "コメントのパースに失敗しました";
    } else if (err == XML_ERROR_PARSING_DECLARATION) {
        return "宣言のパースに失敗しました";
    } else if (err == XML_ERROR_PARSING_UNKNOWN) {
        return "不明なパースエラーです";
    } else if (err == XML_ERROR_EMPTY_DOCUMENT) {
        return "ドキュメントが空です";
    } else if (err == XML_ERROR_MISMATCHED_ELEMENT) {
        return "マッチしない要素です";
    } else if (err == XML_ERROR_PARSING) {
        return "パースエラーです";
    } else if (err == XML_CAN_NOT_CONVERT_TEXT) {
        return "テキストが変換できません";
    } else if (err == XML_NO_TEXT_NODE) {
        return "テキストノードがありません";
    } else {
        return "不明なエラーです";
    }
}

void XMLLoadResourceFile(tinyxml2::XMLDocument& doc, const std::string& filename) throw(GameError)
{
    NSString* filenameStr = [[NSString alloc] initWithCString:filename.c_str() encoding:NSUTF8StringEncoding];

    NSBundle *bundle = [NSBundle mainBundle];
    NSString* path = [bundle pathForResource:filenameStr ofType:nil];
    [filenameStr release];
    if (!path || path.length == 0) {
        throw GameError("XMLファイル \"%s\" が見つかりません。", filename.c_str());
    }

    std::string filepath = path.UTF8String;
    tinyxml2::XMLError error = doc.LoadFile(filepath.c_str());
    if (error != tinyxml2::XML_NO_ERROR) {
        doc.PrintError();
        throw GameError("XMLファイル \"%s\" の読み込みに失敗しました。（%s）", filename.c_str(), XMLErrorToString(error).c_str());
    }
}

void XMLParseString(tinyxml2::XMLDocument& doc, const std::string& str) throw(GameError)
{
    tinyxml2::XMLError error = doc.Parse(str.c_str());
    if (error != tinyxml2::XML_NO_ERROR) {
        doc.PrintError();
        throw GameError("XML parsing error: %s", XMLErrorToString(error).c_str());
    }
}

