//
//  Debug.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <string>

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include "Types.hpp"
#include "StringSupport.hpp"


#define DebugLog(...)   { _Log(__FILE__, __LINE__, __VA_ARGS__); }
#define DebugLogWarning(...)   { _LogWarning(__FILE__, __LINE__, __VA_ARGS__); }
#define DebugLogError(...)   { _LogError(__FILE__, __LINE__, __VA_ARGS__); }


void _Log(const std::string& filepath, int lineNum, const char* format, ...);
void _LogWarning(const std::string& filepath, int lineNum, const char* format, ...);
void _LogError(const std::string& filepath, int lineNum, const char* format, ...);


#endif  //#ifndef __DEBUG_HPP__


