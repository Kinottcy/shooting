//
//  GMOpenGLView.hpp
//  Game Framework
//
//  Created by numata on Dec 25, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GM_OPENGL_VIEW_HPP__
#define __GM_OPENGL_VIEW_HPP__


#import <Cocoa/Cocoa.h>

#include "GMGame.hpp"
#include "Input.hpp"


@interface GMOpenGLView : NSOpenGLView {
    // アニメーションサポートのための変数
    CGLContextObj   mCGLContext;    // Core OpenGL のコンテキスト
    BOOL            mIsRunning;     // ゲームを実行中かどうか
    BOOL            mIsFinished;    // スレッドが完了しているか
    
    // ゲーム関係の変数
    GMGame*         mGameInst;

    bool            mIsShiftKeyDown;
    int             mShiftKeyState;
}

- (GMGame*)game;
- (void)finishGame;

@end


#endif  //#ifndef __GM_OPENGL_VIEW_HPP__

