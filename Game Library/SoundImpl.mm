//
//  SoundImpl.mm
//  Game Framework
//
//  Created by numata on July 24, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#import "SoundImpl.hpp"
#import "GameError.hpp"


static ALCdevice*   sALDevice = NULL;
static ALCcontext*  sALContext = NULL;


void __InitOpenAL()
{
    if (sALDevice != NULL) {
        return;
    }
    
    sALDevice = alcOpenDevice(NULL);
    sALContext = alcCreateContext(sALDevice, NULL);
    alcMakeContextCurrent(sALContext);
}

void __CleanUpOpenAL()
{
    if (sALDevice == NULL) {
        return;
    }
    
    alcMakeContextCurrent(NULL);
    alcDestroyContext(sALContext);
    alcCloseDevice(sALDevice);
}


static float    sListenerHorizontalOrientation    = 0.0f;
static float    sListenerPos[3]         = { 0.0f, 0.0f, 0.0f };


@implementation SoundImpl

+ (float)listenerHorizontalOrientation
{
    return sListenerHorizontalOrientation;
}

+ (void)setListenerHorizontalOrientation:(float)radAngle
{
    if (sListenerHorizontalOrientation == radAngle) {
        return;
    }
    
    sListenerHorizontalOrientation = radAngle;
    
    ALenum error = AL_NO_ERROR;
	float orientation[6] = { 0.0f, 0.0f, -1.0f,    // direction
                             0.0f, 1.0f, 0.0f };   //up	
    
	orientation[0] = sinf(radAngle);
	orientation[1] = 0.0f;			// No Change to the Y vector
	orientation[2] = -cosf(radAngle);	
    
	alListenerfv(AL_ORIENTATION, orientation);
	if ((error = alGetError()) != AL_NO_ERROR) {
		throw GameError("OpenALのリスナー位置の設定に失敗しました。");
    }
}

+ (void)getListenerX:(float*)x y:(float*)y z:(float*)z
{
    *x = sListenerPos[0];
    *y = sListenerPos[1];
    *z = sListenerPos[2];
}

+ (void)setListenerX:(float)x y:(float)y z:(float)z
{
    sListenerPos[0] = x;
    sListenerPos[1] = y;
    sListenerPos[2] = z;
	alListenerfv(AL_POSITION, sListenerPos);    
}

- (id)initWithName:(NSString*)name doLoop:(BOOL)doLoop
{
    self = [super init];
    if (self) {
        mPitch = 1.0f;
        mVolume = 0.0f;
        
        mSourcePos[0] = 0.0f;
        mSourcePos[1] = 0.0f;
        mSourcePos[2] = 0.0f;
        
        mAudioBuffer = NULL;
        
        NSURL* url = [[NSBundle mainBundle] URLForResource:[name stringByDeletingPathExtension] withExtension:[name pathExtension]];
        
        if (!url) {
            throw GameError("サウンドファイル \"%s\" が見つかりません。ファイル名を確認してください。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        OSStatus    err;
        UInt32      size;
        
        // オーディオファイルを開く
        ExtAudioFileRef audioFile;
        err = ExtAudioFileOpenURL((__bridge CFURLRef)url, &audioFile);

        if (err != noErr) {
            throw GameError("サウンドファイル \"%@\" のオープンに失敗しました。ファイル形式を確認してください。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        // オーディオデータフォーマットを取得する
        AudioStreamBasicDescription fileFormat;
        size = sizeof(fileFormat);
        err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileDataFormat, &size, &fileFormat);
        if (err != errSecSuccess) {
            throw GameError("サウンドファイル \"%s\" のデータ形式の確認に失敗しました。ファイル形式を確認してください。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }

        // アウトプットフォーマットを設定する
        AudioStreamBasicDescription outputFormat;
        outputFormat.mSampleRate = fileFormat.mSampleRate;
        outputFormat.mChannelsPerFrame = fileFormat.mChannelsPerFrame;
        outputFormat.mFormatID = kAudioFormatLinearPCM;
        outputFormat.mBytesPerPacket = 2 * outputFormat.mChannelsPerFrame;
        outputFormat.mFramesPerPacket = 1;
        outputFormat.mBytesPerFrame = 2 * outputFormat.mChannelsPerFrame;
        outputFormat.mBitsPerChannel = 16;
        outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
        err = ExtAudioFileSetProperty(audioFile, kExtAudioFileProperty_ClientDataFormat, sizeof(outputFormat), &outputFormat);
        if (err != errSecSuccess) {
            throw GameError("サウンドファイル \"%s\" を再生するためのオーディオ出力の設定に失敗しました。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }

        mSampleRate = (ALsizei)outputFormat.mSampleRate;
        mOutputFormat = (outputFormat.mChannelsPerFrame > 1)? AL_FORMAT_STEREO16: AL_FORMAT_MONO16;
        
        // フレーム数を取得する
        SInt64  fileLengthFrames = 0;
        size = sizeof(fileLengthFrames);
        err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileLengthFrames, &size, &fileLengthFrames);
        if (err != errSecSuccess) {
            throw GameError("サウンドファイル \"%s\" の長さの取得に失敗しました。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }

        // バッファを用意する
        mDataSize = (ALsizei)(fileLengthFrames * outputFormat.mBytesPerFrame);
        mAudioBuffer = (float*)malloc(mDataSize);
        
        AudioBufferList dataBuffer;
        dataBuffer.mNumberBuffers = 1;
        dataBuffer.mBuffers[0].mDataByteSize = mDataSize;
        dataBuffer.mBuffers[0].mNumberChannels = outputFormat.mChannelsPerFrame;
        dataBuffer.mBuffers[0].mData = mAudioBuffer;
        
        // バッファにデータを読み込む
        UInt32 theFileLengthFrames = (UInt32)fileLengthFrames;
        err = ExtAudioFileRead(audioFile, &theFileLengthFrames, &dataBuffer);
        if (err != errSecSuccess) {
            throw GameError("サウンドファイル \"%s\" からのデータ読み込みに失敗しました。", [name cStringUsingEncoding:NSUTF8StringEncoding]);
        }

        // オーディオファイルを破棄する
        ExtAudioFileDispose(audioFile);
        
        // バッファとソースを作成する
        alGenBuffers(1, &mALBuffer);
        alGenSources(1, &mALSource);
        
        // データをバッファに設定する
        alBufferData(mALBuffer, mOutputFormat, mAudioBuffer, mDataSize, mSampleRate);
        
        // バッファをソースに設定する
        alSourcei(mALSource, AL_BUFFER, mALBuffer);
        
        // ループを設定する
        alSourcei(mALSource, AL_LOOPING, (doLoop? AL_TRUE: AL_FALSE));
        
        // ボリュームの設定
        [self setVolume:1.0f];        
    }
    return self;
}

- (void)dealloc
{
    alSourceStop(mALSource);
    
    alDeleteBuffers(1, &mALBuffer);
    alDeleteSources(1, &mALSource);
    
    if (mAudioBuffer != NULL) {
        free(mAudioBuffer);
    }

    [super dealloc];
}

- (void)play
{
    alSourcePlay(mALSource);
}

- (void)pause
{
    alSourcePause(mALSource);
}

- (void)stop
{
    alSourceStop(mALSource);
    alSourceRewind(mALSource);
}

- (BOOL)isPlaying
{
    ALint state;
    alGetSourcei(mALSource, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING)? YES: NO;
}

- (BOOL)isPaused
{
    ALint state;
    alGetSourcei(mALSource, AL_SOURCE_STATE, &state);
    return (state == AL_PAUSED)? YES: NO;
}

- (void)getSourceX:(float*)x y:(float*)y z:(float*)z
{
    *x = mSourcePos[0];
    *y = mSourcePos[1];
    *z = mSourcePos[2];
}

- (void)setSourceX:(float)x y:(float)y z:(float)z
{
    mSourcePos[0] = x;
    mSourcePos[1] = y;
    mSourcePos[2] = z;
    alSourcefv(mALSource, AL_POSITION, mSourcePos);
}

- (float)pitch
{
    return mPitch;
}

/* pitch can be between 0.5-2.0. Default 1.0. */
- (void)setPitch:(float)pitch
{
    /*if (pitch > 2.0) {
        pitch = 2.0;
    } else if (pitch < 0.5) {
        pitch = 0.5;
    }*/
    if (mPitch == pitch) {
        return;
    }
    mPitch = pitch;
    alSourcef(mALSource, AL_PITCH, mPitch);
}

- (float)volume
{
    return mVolume;
}

- (void)setVolume:(float)volume
{
    if (volume < 0.0f) {
        volume = 0.0f;
    }
    if (mVolume == volume) {
        return;
    }
    mVolume = volume;
    alSourcef(mALSource, AL_GAIN, mVolume);
}

@end


