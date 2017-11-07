//
//  GMGame.cpp
//  Game Framework
//
//  Created by numata on Jan 04, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "GMGame.hpp"
#include "GameError.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "Globals.hpp"


static GMGame* sInstance = 0;


void    __InitSimple2D();
void    __OutputPrintStrings();
void    __InitTextFontInfo();
void    __CleanUpTextTextures();
void    Update();


static Matrix4x4 initialProjectionMatrix;


GMGame* GMGame::GetInstance()
{
    return sInstance;
}


GMGame::GMGame()
    : mTitle("Game"), mStartUpColor(Color::black)
{
    sInstance = this;
    SetTitle(GAME_TITLE);
}

void GMGame::SetUp()
{
    renderer = new BaseRenderer();
    camera = new Camera();
    initialProjectionMatrix = Matrix4x4::Ortho(0.0f, Screen::width, 0.0f, Screen::height, -1.0f, 1.0f);
}

GMGame::~GMGame()
{
    delete renderer;
    delete camera;

    for (auto& kv : soundMap) {
        delete kv.second;
    }
    soundMap.clear();

    for (auto& kv : musicMap) {
        delete kv.second;
    }
    musicMap.clear();

    for (auto& kv : textureMap) {
        delete kv.second;
    }
    textureMap.clear();
}

void GMGame::SetStartUpColor(const Color& color)
{
    mStartUpColor = color;
}

void GMGame::SetTitle(const std::string& str)
{
    mTitle = str;
}

Color GMGame::GetStartUpColor() const
{
    return mStartUpColor;
}

std::string GMGame::GetTitle() const
{
    return mTitle;
}


#pragma mark ==== ゲーム進行 ====

void GMGame::Render()
{
    __InitSimple2D();

    camera->SetProjectionMatrix(initialProjectionMatrix);
    camera->Set();
    renderer->SetBlendMode(BlendModeAlpha);
    renderer->Start();
    
    __InitTextFontInfo();
    
    Update();

    renderer->SetBlendMode(BlendModeAlpha);
    __OutputPrintStrings();
    renderer->End();
    
    __CleanUpTextTextures();
}

Music* GMGame::LoadMusic(const std::string& filename, bool loop)
{
    Music *ret = musicMap[filename];
    if (!ret) {
        ret = new Music(filename, loop);
        musicMap[filename] = ret;
    }
    return ret;
}

Sound* GMGame::LoadSound(const std::string& filename, bool loop)
{
    Sound *ret = soundMap[filename];
    if (!ret) {
        ret = new Sound(filename, loop);
        soundMap[filename] = ret;
    }
    return ret;
}

Texture* GMGame::LoadTexture(const std::string& filename)
{
    Texture *ret = textureMap[filename];
    if (!ret) {
        ret = new Texture(filename);
        textureMap[filename] = ret;
    }
    return ret;
}


