//
//  GameFramework.hpp
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GAME_FRAMEWORK_HPP__
#define __GAME_FRAMEWORK_HPP__

// Standard Libraries
#include <OpenGL/glu.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Types.hpp"
#include "GameError.hpp"
#include "GMGame.hpp"
#include "Input.hpp"
#include "Random.hpp"
#include "StringSupport.hpp"
#include "Time.hpp"

// Graphics Core
#include "GL_class.hpp"
#include "DrawBatch.hpp"

// Graphics
#include "Camera.hpp"
#include "Screen.hpp"
#include "BaseRenderer.hpp"
#include "RenderTarget.hpp"

// Simple API
#include "SimpleMedia.hpp"
#include "Simple2D.hpp"

// Resource Management
#include "XmlDocument.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "Texture.hpp"
#include "File.hpp"

// Debugging Support
#include "Debug.hpp"


using namespace std;
using namespace Game;


#endif  //#ifndef __GAME_FRAMEWORK_HPP__

