//
//  SimpleMedia.cpp
//  Game Framework
//
//  Created by numata on 2016/12/18.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "SimpleMedia.hpp"
#include "Globals.hpp"


static Music *backgroundMusic = 0;
static float bgmVolume = 1.0f;
static float musicRate = 1.0f;


void PlayBGM(const std::string& filename)
{
    if (backgroundMusic) {
        backgroundMusic->Stop();
    }
    __gGMLastErrorPlace = "PlayBGM()";
    backgroundMusic = GMGame::GetInstance()->LoadMusic(filename);
    backgroundMusic->SetVolume(bgmVolume);
    backgroundMusic->SetRate(musicRate);
    backgroundMusic->Play();
}

void PlayBGM()
{
    __gGMLastErrorPlace = "PlayBGM()";
    if (backgroundMusic) {
        backgroundMusic->Play();
    }
}

void PauseBGM()
{
    if (backgroundMusic) {
        if (backgroundMusic->IsPlaying()) {
            backgroundMusic->Pause();
        } else {
            backgroundMusic->Play();
        }
    }
}

void StopBGM()
{
    if (backgroundMusic) {
        backgroundMusic->Stop();
    }
}

void SetBGMRate(float rate)
{
    assert(rate > 0.0f);

    musicRate = rate;
    if (backgroundMusic) {
        backgroundMusic->SetRate(rate);
    }
}

void SetBGMVolume(float volume)
{
    assert(volume >= 0.0f);

    bgmVolume = volume;
    if (backgroundMusic) {
        backgroundMusic->SetVolume(bgmVolume);
    }
}


void PlaySound(const std::string& filename)
{
    PlaySound(filename, 1.0f);
}

void PlaySound(const std::string& filename, float volume)
{
    __gGMLastErrorPlace = "PlaySound()";
    Sound *sound = GMGame::GetInstance()->LoadSound(filename);
    if (sound->IsPlaying()) {
        sound->Stop();
    }
    sound->SetVolume(volume);
    sound->Play();
}

