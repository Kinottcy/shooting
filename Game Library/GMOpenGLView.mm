//
//  GMOpenGLView.mm
//  Game Framework
//
//  Created by numata on Dec 25, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#import "GMOpenGLView.hpp"
#include "GameError.hpp"
#import <OpenGL/OpenGL.h>
#import <OpenGL/glu.h>
#import <mach/mach.h>
#import <mach/mach_time.h>
#include <sys/time.h>
#import "GMAppDelegate.hpp"
#include "GL_class.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "Time.hpp"
#include "DrawBatch.hpp"
#include "Globals.hpp"


static bool sHasShownError = false;


void    Start();


// OpenGL の型とサイズ
//     GLubyte (1byte): 0〜255
//     GLshort (2byte): -32768〜32767

// XIB における NSOpenGLView の設定について
//     ※ ウィンドウの「One Shot」設定は OFF にしておくこと。
//     Color: カラーバッファのサイズ
//     Depth: デプスバッファのサイズ
//     Stencil: ステンシルバッファのサイズ
//     Accum: アキュムレーションバッファのサイズ（glAccum() で操作する）
//     Auxiliary Buffers: 補助バッファのサイズ。使い方はユーザ次第。
//     Buffer: ダブルバッファリングの指定
//     Sampling: マルチサンプルの指定（アンチエイリアスの方法）
//     Renderer: 
//         Accelerated: Hardware-accelerated → 通常の Accelerated の順でレンダラを選択する。（基本的にこれを使う）
//         Allow Offline: 速度よりも優先してオフラインレンダリングを行う。基本的に遅いので ON にするべきではない。
//         No Recovery: Accelerated renderer がリソース不足で失敗した場合に、OpenGL が他のレンダラにスイッチしないようにするかどうかを指定する。
//                      どの道、リソース不足になるのが異常事態なので、どっちでもあまり変わらないと思う。
//                      いちおう OFF にしておいた方がユーザには優しいのかな？
//     Policy: 指定に合致するピクセルフォーマットの選択ポリシー
//         Minimum: 最低でも要求されたバッファサイズ以上のサイズが選択される。
//         Maximum: ゼロでないバッファサイズが指定された場合、可能な限り大きなバッファサイズが選択される。
//         Closest: 要求されたバッファサイズにもっとも近いカラーバッファのサイズが選択される。
//             Minimum と Maximum はカラーバッファ、デプスバッファ、アキュムレーションバッファのバッファサイズにのみ適用される。
//             Closest はカラーバッファのバッファサイズにのみ適用される。


@implementation GMOpenGLView

/*
    ゲームの初期化を行う。
 */
- (void)prepareGame
{
    mIsShiftKeyDown = false;
    mShiftKeyState = 0;
    
    try {
        // ゲーム本体の作成
        mGameInst = new GMGame();
    } catch (std::exception& e) {
        gGMErrorStr = e.what();
        gGMHasGameStartError = true;
    }
}

- (void)dealloc
{
    delete mGameInst;
    
    [super dealloc];
}

- (GMGame*)game
{
    return mGameInst;
}

/*
    起動時の設定を行う。
 */
- (void)prepareOpenGL
{
    [self setWantsBestResolutionOpenGLSurface:YES];
    NSSize size = NSMakeSize(1, 1);
    size = [self convertSizeToBacking:size];
    if (size.width >= 2.0f) {
        __GMScaleFactor = 2.0f;
    }

    // CGL コンテキストの取得
    mCGLContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    
    // デプステストの設定
    glDisable(GL_DEPTH_TEST);

    // ブレンドモードの設定
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // ビューポート切り取りの設定
    glDisable(GL_SCISSOR_TEST);
    
    // 各種頂点配列操作の有効化・無効化
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // VSYNC を有効にする場合には、以下の2行のコメントアウトを取り除く。ただし、あまり推奨できない。
    // チラツキの対処方法は、あきらめるのがいちばん。ゲームをプレイしている者はそこまで気にしない。
    //GLint sync = 1;
    //CGLSetParameter(mCGLContext, kCGLCPSwapInterval, &sync);

    // グラフィックコンテキストの初期化
    NSSize frameSize = [self frame].size;
    Screen::width = (int)frameSize.width;
    Screen::height = (int)frameSize.height;
    GL::SetViewport(Game::Rect(0.0f, 0.0f, frameSize.width, frameSize.height));

    // ゲームの初期化
    try {
        mGameInst->SetUp();
        Start();
    } catch (std::exception& e) {
        gGMHasGameStartError = true;
        gGMErrorStr = e.what();
    }

    // 表画面と裏画面の両方に描画しておく
    Color startUpColor = mGameInst->GetStartUpColor();
    glClearColor(startUpColor.r, startUpColor.g, startUpColor.b, startUpColor.a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGLFlushDrawable(mCGLContext);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CGLFlushDrawable(mCGLContext);

    // ゲームスレッドの作成
    if (!gGMHasGameStartError) {
        mIsRunning = NO;
        mIsFinished = NO;
        [NSThread detachNewThreadSelector:@selector(gameProc:)
                                 toTarget:self
                               withObject:nil];
    }
}

/*
    画面サイズ変更時の処理を行う。
    → 画面サイズ変更は禁止しておく。
 */
- (void)reshape
{
    NSSize frameSize = [self frame].size;
    frameSize = [self convertSizeToBacking:frameSize];
    GL::SetViewport(Game::Rect(0.0f, 0.0f, frameSize.width, frameSize.height));
}

/*
    描画のメインの処理を行う。
 */
- (void)drawRect:(NSRect)dirtyRect
{
    if (!gGMHasGameStartError && !gGMHasTerminatedWithError) {
        CGLLockContext(mCGLContext);
        CGLSetCurrentContext(mCGLContext);

        try {
            mGameInst->Render();
        } catch (std::exception& e) {
            gGMHasTerminatedWithError = true;
            gGMErrorStr = e.what();
            [self setNeedsDisplay:YES];
        }
        
        CGLFlushDrawable(mCGLContext);
        CGLUnlockContext(mCGLContext);
    } else {
        CGLLockContext(mCGLContext);
        CGLSetCurrentContext(mCGLContext);
        glClearColor(0.8f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CGLFlushDrawable(mCGLContext);
        CGLUnlockContext(mCGLContext);
        
        if (gGMHasTerminatedWithError && !sHasShownError) {
            sHasShownError = YES;
            [NSTimer scheduledTimerWithTimeInterval:0 target:self selector:@selector(showErrorProc:) userInfo:nil repeats:NO];
        }
    }
}

- (void)stopGame
{
    mIsRunning = NO;
}

- (void)gameProc:(id)dummy
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    // ナノ秒から Mach 時間に変換
    mach_timebase_info_data_t timebaseInfo;
    mach_timebase_info(&timebaseInfo);
    uint64_t frameInterval = (uint64_t)(1000000000 / FRAME_RATE) * timebaseInfo.denom / timebaseInfo.numer;
    uint64_t prevTime = mach_absolute_time();
    
    mIsRunning = YES;
    
    gGMHasTerminatedWithError = NO;
    try {
        CGLLockContext(mCGLContext);
        CGLSetCurrentContext(mCGLContext);
        //mGraphics->setViewport(mGraphics->getViewport());
        CGLUnlockContext(mCGLContext);

        while (mIsRunning && !gGMHasTerminatedWithError) {
            // 入力と時間の更新
            Input::__UpdateTriggers();
            Time::__Update();

            // ビューの描画
            CGLLockContext(mCGLContext);
            CGLSetCurrentContext(mCGLContext);
            mGameInst->Render();
            if (gGMIsDrawing) {
                throw GameInvalidOperationError("DrawBatch::End() was not invoked after DrawBatch::Begin().");
            }
            CGLFlushDrawable(mCGLContext);
            CGLUnlockContext(mCGLContext);

            // フレーム数をカウントして休ませる
            Time::frameCount++;
            uint64_t endTime = prevTime + frameInterval;
            prevTime = mach_absolute_time();
            if (endTime > prevTime) {
                mach_wait_until(endTime);
                prevTime = endTime;
            }
        }
    } catch (std::exception& e) {
        CGLUnlockContext(mCGLContext);
        if (!gGMHasTerminatedWithError) {
            gGMHasTerminatedWithError = YES;
            sHasShownError = YES;
            gGMErrorStr = e.what();
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                [self showErrorProc:nil];
            }];
        }
    }

    delete mGameInst;

    mIsFinished = YES;
    
    if (!gGMHasTerminatedWithError) {
        [NSApp replyToApplicationShouldTerminate:YES];
    }
    
    [pool drain];
}

- (void)gameErrorAlertDidEnd:(NSAlert*)alert
                  returnCode:(NSInteger)returnCode
                 contextInfo:(void*)contextInfo
{
    [NSApp terminate:self];
}

- (void)finishGame
{
    mIsFinished = YES;
    if (!gGMHasTerminatedWithError) {
        [NSApp replyToApplicationShouldTerminate:YES];
    }
}

- (void)showErrorProc:(NSTimer *)timer
{
    NSAlert *alert = [NSAlert new];
    alert.alertStyle = NSCriticalAlertStyle;
    alert.messageText = @"実行時エラー";

    NSString *lastErrorPlace = [NSString stringWithCString:__gGMLastErrorPlace.c_str() encoding:NSUTF8StringEncoding];
    NSString *errorStr = [NSString stringWithCString:gGMErrorStr.c_str() encoding:NSUTF8StringEncoding];
    
    if (lastErrorPlace.length > 0) {
        alert.informativeText = [NSString stringWithFormat:@"%@: %@\n\nUpdate() 関数の中でエラーが発生したようです。デバッグ領域のバックトレースも確認してください。", lastErrorPlace, errorStr];
    } else {
        alert.informativeText = [NSString stringWithFormat:@"%@\n\nUpdate() 関数の中でエラーが発生したようです。デバッグ領域のバックトレースも確認してください。", errorStr];
    }
    
    [alert beginSheetModalForWindow:[self window]
                  completionHandler:^(NSModalResponse returnCode) {
                      mIsFinished = YES;
                      [NSApp terminate:self];
                  }];
}

- (void)keyDown:(NSEvent*)theEvent
{
    unsigned short keyCode = [theEvent keyCode];

    if (keyCode == 0x7e) {
        Input::__ProcessKeyDown(KeyMask::UpArrow);
    }
    else if (keyCode == 0x7d) {
        Input::__ProcessKeyDown(KeyMask::DownArrow);
    }
    else if (keyCode == 0x7b) {
        Input::__ProcessKeyDown(KeyMask::LeftArrow);
    }
    else if (keyCode == 0x7c) {
        Input::__ProcessKeyDown(KeyMask::RightArrow);
    }
    else if (keyCode == 0x00) {
        Input::__ProcessKeyDown(KeyMask::A);
    }
    else if (keyCode == 0x0b) {
        Input::__ProcessKeyDown(KeyMask::B);
    }
    else if (keyCode == 0x08) {
        Input::__ProcessKeyDown(KeyMask::C);
    }
    else if (keyCode == 0x02) {
        Input::__ProcessKeyDown(KeyMask::D);
    }
    else if (keyCode == 0x0e) {
        Input::__ProcessKeyDown(KeyMask::E);
    }
    else if (keyCode == 0x03) {
        Input::__ProcessKeyDown(KeyMask::F);
    }
    else if (keyCode == 0x05) {
        Input::__ProcessKeyDown(KeyMask::G);
    }
    else if (keyCode == 0x04) {
        Input::__ProcessKeyDown(KeyMask::H);
    }
    else if (keyCode == 0x22) {
        Input::__ProcessKeyDown(KeyMask::I);
    }
    else if (keyCode == 0x26) {
        Input::__ProcessKeyDown(KeyMask::J);
    }
    else if (keyCode == 0x28) {
        Input::__ProcessKeyDown(KeyMask::K);
    }
    else if (keyCode == 0x25) {
        Input::__ProcessKeyDown(KeyMask::L);
    }
    else if (keyCode == 0x2e) {
        Input::__ProcessKeyDown(KeyMask::M);
    }
    else if (keyCode == 0x2d) {
        Input::__ProcessKeyDown(KeyMask::N);
    }
    else if (keyCode == 0x1f) {
        Input::__ProcessKeyDown(KeyMask::O);
    }
    else if (keyCode == 0x23) {
        Input::__ProcessKeyDown(KeyMask::P);
    }
    else if (keyCode == 0x0c) {
        Input::__ProcessKeyDown(KeyMask::Q);
    }
    else if (keyCode == 0x0f) {
        Input::__ProcessKeyDown(KeyMask::R);
    }
    else if (keyCode == 0x01) {
        Input::__ProcessKeyDown(KeyMask::S);
    }
    else if (keyCode == 0x11) {
        Input::__ProcessKeyDown(KeyMask::T);
    }
    else if (keyCode == 0x20) {
        Input::__ProcessKeyDown(KeyMask::U);
    }
    else if (keyCode == 0x09) {
        Input::__ProcessKeyDown(KeyMask::V);
    }
    else if (keyCode == 0x0d) {
        Input::__ProcessKeyDown(KeyMask::W);
    }
    else if (keyCode == 0x07) {
        Input::__ProcessKeyDown(KeyMask::X);
    }
    else if (keyCode == 0x10) {
        Input::__ProcessKeyDown(KeyMask::Y);
    }
    else if (keyCode == 0x06) {
        Input::__ProcessKeyDown(KeyMask::Z);
    }
    else if (keyCode == 0x1d) {
        Input::__ProcessKeyDown(KeyMask::Alpha0);
    }
    else if (keyCode == 0x12) {
        Input::__ProcessKeyDown(KeyMask::Alpha1);
    }
    else if (keyCode == 0x13) {
        Input::__ProcessKeyDown(KeyMask::Alpha2);
    }
    else if (keyCode == 0x14) {
        Input::__ProcessKeyDown(KeyMask::Alpha3);
    }
    else if (keyCode == 0x15) {
        Input::__ProcessKeyDown(KeyMask::Alpha4);
    }
    else if (keyCode == 0x17) {
        Input::__ProcessKeyDown(KeyMask::Alpha5);
    }
    else if (keyCode == 0x16) {
        Input::__ProcessKeyDown(KeyMask::Alpha6);
    }
    else if (keyCode == 0x1a) {
        Input::__ProcessKeyDown(KeyMask::Alpha7);
    }
    else if (keyCode == 0x1c) {
        Input::__ProcessKeyDown(KeyMask::Alpha8);
    }
    else if (keyCode == 0x19) {
        Input::__ProcessKeyDown(KeyMask::Alpha9);
    }
    else if (keyCode == 0x31) {
        Input::__ProcessKeyDown(KeyMask::Space);
    }
    else if (keyCode == 0x35) {
        Input::__ProcessKeyDown(KeyMask::Escape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        Input::__ProcessKeyDown(KeyMask::Return);
    }
    else if (keyCode == 0x33) {
        Input::__ProcessKeyDown(KeyMask::Backspace);
    }
    else if (keyCode == 0x30) {
        Input::__ProcessKeyDown(KeyMask::Tab);
    }
    else if (keyCode == 0x75) {
        Input::__ProcessKeyDown(KeyMask::Delete);
    }
    else if (keyCode == 0x52) {
        Input::__ProcessKeyDown(KeyMask::Keypad0);
    }
    else if (keyCode == 0x53) {
        Input::__ProcessKeyDown(KeyMask::Keypad1);
    }
    else if (keyCode == 0x54) {
        Input::__ProcessKeyDown(KeyMask::Keypad2);
    }
    else if (keyCode == 0x55) {
        Input::__ProcessKeyDown(KeyMask::Keypad3);
    }
    else if (keyCode == 0x56) {
        Input::__ProcessKeyDown(KeyMask::Keypad4);
    }
    else if (keyCode == 0x57) {
        Input::__ProcessKeyDown(KeyMask::Keypad5);
    }
    else if (keyCode == 0x58) {
        Input::__ProcessKeyDown(KeyMask::Keypad6);
    }
    else if (keyCode == 0x59) {
        Input::__ProcessKeyDown(KeyMask::Keypad7);
    }
    else if (keyCode == 0x5b) {
        Input::__ProcessKeyDown(KeyMask::Keypad8);
    }
    else if (keyCode == 0x5c) {
        Input::__ProcessKeyDown(KeyMask::Keypad9);
    }
    else {
        //printf("非対応のkeyDown: 0x%02x\n", keyCode);
    }
}

- (void)flagsChanged:(NSEvent*)theEvent
{
    NSUInteger modifierFlags = [theEvent modifierFlags];

    if (modifierFlags & NSShiftKeyMask) {
        mIsShiftKeyDown = true;
    } else if (mIsShiftKeyDown) {
        mIsShiftKeyDown = false;
    }

    int shiftKeyState = modifierFlags & 0x6;
    if (mIsShiftKeyDown) {
        if (shiftKeyState & 0x2 && !(mShiftKeyState & 0x2)) {
            Input::__ProcessKeyDown(KeyMask::LeftShift);
        }
        if (!(shiftKeyState & 0x2) && (mShiftKeyState & 0x2)) {
            Input::__ProcessKeyUp(KeyMask::LeftShift);
        }
        if (shiftKeyState & 0x4 && !(mShiftKeyState & 0x4)) {
            Input::__ProcessKeyDown(KeyMask::RightShift);
        }
        if (!(shiftKeyState & 0x4) && (mShiftKeyState & 0x4)) {
            Input::__ProcessKeyUp(KeyMask::RightShift);
        }
    } else {
        if (!(shiftKeyState & 0x2) && (mShiftKeyState & 0x2)) {
            Input::__ProcessKeyUp(KeyMask::LeftShift);
        }
        if (!(shiftKeyState & 0x4) && (mShiftKeyState & 0x4)) {
            Input::__ProcessKeyUp(KeyMask::RightShift);
        }
    }

    mShiftKeyState = shiftKeyState;
}

- (void)keyUp:(NSEvent*)theEvent
{
    unsigned short keyCode = [theEvent keyCode];

    if (keyCode == 0x7e) {
        Input::__ProcessKeyUp(KeyMask::UpArrow);
    }
    else if (keyCode == 0x7d) {
        Input::__ProcessKeyUp(KeyMask::DownArrow);
    }
    else if (keyCode == 0x7b) {
        Input::__ProcessKeyUp(KeyMask::LeftArrow);
    }
    else if (keyCode == 0x7c) {
        Input::__ProcessKeyUp(KeyMask::RightArrow);
    }
    else if (keyCode == 0x00) {
        Input::__ProcessKeyUp(KeyMask::A);
    }
    else if (keyCode == 0x0b) {
        Input::__ProcessKeyUp(KeyMask::B);
    }
    else if (keyCode == 0x08) {
        Input::__ProcessKeyUp(KeyMask::C);
    }
    else if (keyCode == 0x02) {
        Input::__ProcessKeyUp(KeyMask::D);
    }
    else if (keyCode == 0x0e) {
        Input::__ProcessKeyUp(KeyMask::E);
    }
    else if (keyCode == 0x03) {
        Input::__ProcessKeyUp(KeyMask::F);
    }
    else if (keyCode == 0x05) {
        Input::__ProcessKeyUp(KeyMask::G);
    }
    else if (keyCode == 0x04) {
        Input::__ProcessKeyUp(KeyMask::H);
    }
    else if (keyCode == 0x22) {
        Input::__ProcessKeyUp(KeyMask::I);
    }
    else if (keyCode == 0x26) {
        Input::__ProcessKeyUp(KeyMask::J);
    }
    else if (keyCode == 0x28) {
        Input::__ProcessKeyUp(KeyMask::K);
    }
    else if (keyCode == 0x25) {
        Input::__ProcessKeyUp(KeyMask::L);
    }
    else if (keyCode == 0x2e) {
        Input::__ProcessKeyUp(KeyMask::M);
    }
    else if (keyCode == 0x2d) {
        Input::__ProcessKeyUp(KeyMask::N);
    }
    else if (keyCode == 0x1f) {
        Input::__ProcessKeyUp(KeyMask::O);
    }
    else if (keyCode == 0x23) {
        Input::__ProcessKeyUp(KeyMask::P);
    }
    else if (keyCode == 0x0c) {
        Input::__ProcessKeyUp(KeyMask::Q);
    }
    else if (keyCode == 0x0f) {
        Input::__ProcessKeyUp(KeyMask::R);
    }
    else if (keyCode == 0x01) {
        Input::__ProcessKeyUp(KeyMask::S);
    }
    else if (keyCode == 0x11) {
        Input::__ProcessKeyUp(KeyMask::T);
    }
    else if (keyCode == 0x20) {
        Input::__ProcessKeyUp(KeyMask::U);
    }
    else if (keyCode == 0x09) {
        Input::__ProcessKeyUp(KeyMask::V);
    }
    else if (keyCode == 0x0d) {
        Input::__ProcessKeyUp(KeyMask::W);
    }
    else if (keyCode == 0x07) {
        Input::__ProcessKeyUp(KeyMask::X);
    }
    else if (keyCode == 0x10) {
        Input::__ProcessKeyUp(KeyMask::Y);
    }
    else if (keyCode == 0x06) {
        Input::__ProcessKeyUp(KeyMask::Z);
    }
    else if (keyCode == 0x1d) {
        Input::__ProcessKeyUp(KeyMask::Alpha0);
    }
    else if (keyCode == 0x12) {
        Input::__ProcessKeyUp(KeyMask::Alpha1);
    }
    else if (keyCode == 0x13) {
        Input::__ProcessKeyUp(KeyMask::Alpha2);
    }
    else if (keyCode == 0x14) {
        Input::__ProcessKeyUp(KeyMask::Alpha3);
    }
    else if (keyCode == 0x15) {
        Input::__ProcessKeyUp(KeyMask::Alpha4);
    }
    else if (keyCode == 0x17) {
        Input::__ProcessKeyUp(KeyMask::Alpha5);
    }
    else if (keyCode == 0x16) {
        Input::__ProcessKeyUp(KeyMask::Alpha6);
    }
    else if (keyCode == 0x1a) {
        Input::__ProcessKeyUp(KeyMask::Alpha7);
    }
    else if (keyCode == 0x1c) {
        Input::__ProcessKeyUp(KeyMask::Alpha8);
    }
    else if (keyCode == 0x19) {
        Input::__ProcessKeyUp(KeyMask::Alpha9);
    }
    else if (keyCode == 0x31) {
        Input::__ProcessKeyUp(KeyMask::Space);
    }
    else if (keyCode == 0x35) {
        Input::__ProcessKeyUp(KeyMask::Escape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        Input::__ProcessKeyUp(KeyMask::Return);
    }
    else if (keyCode == 0x33) {
        Input::__ProcessKeyUp(KeyMask::Backspace);
    }
    else if (keyCode == 0x30) {
        Input::__ProcessKeyUp(KeyMask::Tab);
    }
    else if (keyCode == 0x75) {
        Input::__ProcessKeyUp(KeyMask::Delete);
    }
    else if (keyCode == 0x52) {
        Input::__ProcessKeyUp(KeyMask::Keypad0);
    }
    else if (keyCode == 0x53) {
        Input::__ProcessKeyUp(KeyMask::Keypad1);
    }
    else if (keyCode == 0x54) {
        Input::__ProcessKeyUp(KeyMask::Keypad2);
    }
    else if (keyCode == 0x55) {
        Input::__ProcessKeyUp(KeyMask::Keypad3);
    }
    else if (keyCode == 0x56) {
        Input::__ProcessKeyUp(KeyMask::Keypad4);
    }
    else if (keyCode == 0x57) {
        Input::__ProcessKeyUp(KeyMask::Keypad5);
    }
    else if (keyCode == 0x58) {
        Input::__ProcessKeyUp(KeyMask::Keypad6);
    }
    else if (keyCode == 0x59) {
        Input::__ProcessKeyUp(KeyMask::Keypad7);
    }
    else if (keyCode == 0x5b) {
        Input::__ProcessKeyUp(KeyMask::Keypad8);
    }
    else if (keyCode == 0x5c) {
        Input::__ProcessKeyUp(KeyMask::Keypad9);
    }
}

- (void)mouseDown:(NSEvent*)theEvent
{
    Input::__ProcessMouseDown();
}

- (void)mouseUp:(NSEvent*)theEvent
{
    Input::__ProcessMouseUp();
}

- (void)rightMouseDown:(NSEvent*)theEvent
{
    Input::__ProcessMouseDownRight();
}

- (void)rightMouseUp:(NSEvent*)theEvent
{
    Input::__ProcessMouseUpRight();
}

@end

