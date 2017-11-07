//
//  Screen.cpp
//  Game Framework
//
//  Created by numata on Jun 26, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "Screen.hpp"


int Screen::width = 0;
int Screen::height = 0;

Vector2 Screen::size()
{
    return Vector2(width, height);
}

