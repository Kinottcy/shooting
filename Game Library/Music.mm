//
//  Music.mm
//  Game Framework
//
//  Created by numata on July 23, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#include "Music.hpp"

#import <AVFoundation/AVFoundation.h>


Music::Music(const std::string& filename, bool loop) throw(GameError)
{
    mFileName = filename;
    mDoLoop = loop;

    mIsPausing = false;
    mAudioPlayer = nil;
    mBGMID = -1;
    
    NSString* filenameStr = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];

    NSURL* url = [[NSBundle mainBundle] URLForResource:[filenameStr stringByDeletingPathExtension] withExtension:[filenameStr pathExtension]];

    if (url) {
        NSError* error = nil;
        mAudioPlayer = (void *)CFBridgingRetain([[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error]);
        [(__bridge AVAudioPlayer*)mAudioPlayer prepareToPlay];
        [(__bridge AVAudioPlayer*)mAudioPlayer setEnableRate:YES];
    }
    if (!mAudioPlayer) {
        throw GameError("音楽ファイル \"%s\" の読み込みに失敗しました。", filename.c_str());
    }
    if (loop) {
        ((__bridge AVAudioPlayer*)mAudioPlayer).numberOfLoops = -1;
    }
}


Music::~Music()
{
    Stop();

    if (mAudioPlayer) {
        CFBridgingRelease(mAudioPlayer);
        mAudioPlayer = nil;
    }
}

std::string Music::GetFileName() const
{
    return mFileName;
}

bool Music::IsPlaying() const
{
    if (mAudioPlayer) {
        return ((__bridge AVAudioPlayer*)mAudioPlayer).playing;
    }
    return false;
}

void Music::Play()
{
    if (mAudioPlayer) {
        if (!mIsPausing) {
            ((__bridge AVAudioPlayer*)mAudioPlayer).currentTime = 0.0f;
        }
        [(__bridge AVAudioPlayer*)mAudioPlayer play];
    }

    mIsPausing = false;
}

void Music::Pause()
{
    if (mAudioPlayer) {
        [(__bridge AVAudioPlayer*)mAudioPlayer pause];
    }
    mIsPausing = true;
}

void Music::SetRate(float rate)
{
    if (mAudioPlayer) {
        [(__bridge AVAudioPlayer*)mAudioPlayer setRate:rate];
    }
}

void Music::Stop()
{
    if (mAudioPlayer) {
        [(__bridge AVAudioPlayer*)mAudioPlayer pause];
        ((__bridge AVAudioPlayer*)mAudioPlayer).currentTime = 0.0f;
    }
    mIsPausing = false;
}

float Music::GetVolume() const
{
    if (mAudioPlayer) {
        return ((__bridge AVAudioPlayer*)mAudioPlayer).volume;
    }
    return 0.0f;
}

void Music::SetVolume(float value)
{
    if (mAudioPlayer) {
        ((__bridge AVAudioPlayer*)mAudioPlayer).volume = value;
    }
}

std::string Music::ToString() const
{
    return "Music(\"" + mFileName + "\", loop=" + (mDoLoop? "true": "false") + ")";
}

