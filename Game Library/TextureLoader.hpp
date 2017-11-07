//
//  TextureLoader.hpp
//  Game Framework
//
//  Created by numata on Dec 31, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __TEXTURE_LOADER_HPP__
#define __TEXTURE_LOADER_HPP__


#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <string>
#include "Types.hpp"
#include "Color.hpp"


enum TextureScaleMode {
    TextureScaleModeLinear,
    TextureScaleModeNearest,
};


GLuint __CreateStringTexture(const std::string& str, TextureScaleMode scaleMode, const std::string& fontName, float fontSize, Vector2* imageSize, GLushort *resizedWidth, GLushort *resizedHeight);

GLuint __LoadTexture(const std::string& imageNameCpp, TextureScaleMode scaleMode, Vector2* imageSize, GLushort* resizedWidth, GLushort* resizedHeight, bool& isFileExistingError);


#endif  //#ifndef __TEXTURE_2D_LOADER_HPP__


