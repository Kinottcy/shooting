//
//  tinyxml2_util.hpp
//  Game Framework
//
//  Created by numata on July 15, 2014.
//  Copyright (c) 2014-2016 Satoshi Numata. All rights reserved.
//

#ifndef __TINYXML2_UTIL_HPP__
#define __TINYXML2_UTIL_HPP__

#include <string>
#include "tinyxml2.h"
#include "GameError.hpp"


std::string XMLErrorToString(tinyxml2::XMLError err);
void XMLLoadResourceFile(tinyxml2::XMLDocument& doc, const std::string& filename) throw(GameError);
void XMLParseString(tinyxml2::XMLDocument& doc, const std::string& str) throw(GameError);


#endif  //#ifndef __TINYXML2_UTIL_HPP__


