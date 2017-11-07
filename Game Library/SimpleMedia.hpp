//
//  SimpleMedia.hpp
//  Game Framework
//
//  Created by numata on 2016/12/18.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __SIMPLE_MEDIA_HPP__
#define __SIMPLE_MEDIA_HPP__


#include "GameFramework.hpp"


// BGMの再生
void    PlayBGM(const std::string& filename);
void    PauseBGM();
void    StopBGM();
void    SetBGMRate(float rate);
void    SetBGMVolume(float volume);

// サウンドの再生
void    PlaySound(const std::string& filename);
void    PlaySound(const std::string& filename, float volume);


#endif  //#ifndef __SIMPLE_MEDIA_HPP__
