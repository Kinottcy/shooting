//
//  GMAppDelegate.hpp
//  Game Framework
//
//  Created by Satoshi Numata on 11/08/07.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GMOpenGLView.hpp"


// ゲーム内のエラー処理によってゲームが中断されたかどうか
extern bool         gGMHasTerminatedWithError;


// 起動時にエラーが起こったかどうか（最初のシーンのテクスチャ読み込みなど）
extern bool         gGMHasGameStartError;
extern std::string  gGMErrorStr;


@interface GMAppDelegate : NSObject {
    IBOutlet NSWindow*       window;
    IBOutlet GMOpenGLView*   glView;
}

+ (GMAppDelegate *)sharedInstance;

- (NSWindow *)window;

@end
