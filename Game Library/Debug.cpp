//
//  Debug.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "Debug.hpp"
#include "StringSupport.hpp"


static int count = 0;


void _Log(const std::string& filepath, int lineNum, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
    printf("\t(%s:%d) (%d)\n", GetLastPathComponent(filepath).c_str(), lineNum, ++count);
}

void _LogWarning(const std::string& filepath, int lineNum, const char* format, ...)
{
    printf("⚠️ ");
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
    printf("\t(%s:%d) (%d)\n", GetLastPathComponent(filepath).c_str(), lineNum, ++count);
}

void _LogError(const std::string& filepath, int lineNum, const char* format, ...)
{
    printf("🚫 ");
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
    printf("\t(%s:%d) (%d)\n", GetLastPathComponent(filepath).c_str(), lineNum, ++count);
}

