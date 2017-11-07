//
//  Sound.mm
//  Game Framework
//
//  Created by numata on July 23, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#include "Sound.hpp"
#include "Types.hpp"
#import "SoundImpl.hpp"


static Vector3    sListenerPos;


void __InitSound()
{
    sListenerPos = Vector3::zero;
}


float Sound::GetListenerHorizontalOrientation()
{
    return [SoundImpl listenerHorizontalOrientation];
}

void Sound::SetListenerHorizontalOrientation(float radAngle)
{
    [SoundImpl setListenerHorizontalOrientation:radAngle];
}

Vector3 Sound::GetListenerPos()
{
    return sListenerPos;
}

void Sound::SetListenerPos(float x, float y, float z)
{
    sListenerPos.x = x;
    sListenerPos.y = y;
    sListenerPos.z = z;
    [SoundImpl setListenerX:(float)x y:(float)y z:(float)z];
}

void Sound::SetListenerPos(const Vector3& vec3)
{
    SetListenerPos(vec3.x, vec3.y, vec3.z);
}

Sound::Sound(const std::string& filename, bool doLoop) throw(GameError)
{
    mFileName = filename;
    mDoLoop = doLoop;

    mSourcePos = Vector3::zero;
    
    // Get the path
    NSString* filenameStr = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
    mSoundImpl = (void *)CFBridgingRetain([[SoundImpl alloc] initWithName:filenameStr doLoop:(doLoop? YES: NO)]);
    if (!mSoundImpl) {
        throw GameError("サウンドファイル \"%s\" の読み込みに失敗しました。", filename.c_str());
    }
}

Sound::~Sound()
{
    CFBridgingRelease(mSoundImpl);
}

std::string Sound::GetFileName() const
{
    return mFileName;
}


bool Sound::IsPlaying() const
{
    return [(__bridge SoundImpl*)mSoundImpl isPlaying];
}

void Sound::Play()
{
    if (IsPlaying()) {
        Stop();
    }
    [(__bridge SoundImpl*)mSoundImpl play];
}

void Sound::Stop()
{
    [(__bridge SoundImpl*)mSoundImpl stop];
}

Vector3 Sound::GetSourcePos() const
{
    return mSourcePos;
}

void Sound::SetSourcePos(const Vector3& vec3)
{
    mSourcePos = vec3;
    [(__bridge SoundImpl*)mSoundImpl setSourceX:vec3.x y:vec3.y z:vec3.z];
}

float Sound::GetPitch() const
{
    return [(__bridge SoundImpl*)mSoundImpl pitch];
}

void Sound::SetPitch(float value)
{
    [(__bridge SoundImpl*)mSoundImpl setPitch:value];
}

float Sound::GetVolume() const
{
    return [(__bridge SoundImpl*)mSoundImpl volume];
}

void Sound::SetVolume(float value)
{
    [(__bridge SoundImpl*)mSoundImpl setVolume:value];
}

std::string Sound::ToString() const
{
    return "Sound(\"" + mFileName + "\", loop=" + (mDoLoop? "true": "false") + ")";
}



