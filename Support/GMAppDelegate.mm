//
//  GMAppDelegate.mm
//  Game Framework
//
//  Created by Satoshi Numata on 11/08/07.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#import "GMAppDelegate.hpp"

#import "Settings.hpp"
#import "Sound.hpp"
#import "SoundImpl.hpp"
#import "Globals.hpp"


bool        gGMHasTerminatedWithError   = false;
bool        gGMHasGameStartError        = false;
std::string gGMErrorStr                 = "";


static GMAppDelegate*   sInstance = nil;


@interface GMOpenGLView (Private)

- (void)prepareGame;
- (void)stopGame;

@end


@implementation GMAppDelegate

+ (GMAppDelegate*)sharedInstance
{
    return sInstance;
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    sInstance = self;
    
    __InitSound();
    __InitOpenAL();
    
    [glView prepareGame];

    GMGame* game = [glView game];
    std::string title = game->GetTitle();
    [window setTitle:[NSString stringWithCString:title.c_str()
                                        encoding:NSUTF8StringEncoding]];
    
    [window setContentSize:NSMakeSize((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y)];
    [window center];
    [window makeKeyAndOrderFront:self];
    [window makeFirstResponder:glView];
    
    if (gGMHasGameStartError) {
        [NSTimer scheduledTimerWithTimeInterval:0 target:self selector:@selector(showStartError:) userInfo:nil repeats:NO];
    }
}

- (void)showStartError:(NSTimer *)timer
{
    NSAlert *alert = [NSAlert new];
    alert.alertStyle = NSCriticalAlertStyle;
    alert.messageText = @"起動時のエラー";

    NSString *lastErrorPlace = [NSString stringWithCString:__gGMLastErrorPlace.c_str() encoding:NSUTF8StringEncoding];
    NSString *errorStr = [NSString stringWithCString:gGMErrorStr.c_str() encoding:NSUTF8StringEncoding];
    
    if (lastErrorPlace.length > 0) {
        alert.informativeText = [NSString stringWithFormat:@"%@: %@\n\nStart() 関数の中でエラーが発生したようです。デバッグ領域のバックトレースも確認してください。", lastErrorPlace, errorStr];
    } else {
        alert.informativeText = [NSString stringWithFormat:@"%@\n\nStart() 関数の中でエラーが発生したようです。デバッグ領域のバックトレースも確認してください。", errorStr];
    }

    [alert beginSheetModalForWindow:[self window]
                  completionHandler:^(NSModalResponse returnCode) {
                      [NSApp terminate:self];
                  }];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
    return NSTerminateNow;
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    [NSCursor unhide];
    [glView stopGame];
    __CleanUpOpenAL();
}

- (NSWindow*)window
{
    return window;
}

@end

