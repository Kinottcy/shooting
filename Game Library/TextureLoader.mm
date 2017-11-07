//
//  TextureLoader.mm
//  Game Framework
//
//  Created by numata on Dec 31, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#import "TextureLoader.hpp"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import "Globals.hpp"


static CGColorSpaceRef sColorSpaceRef = NULL;
static NSMutableData *sBitmapData = nil;
static NSUInteger sBitmapLength = 0;
static NSMutableDictionary *sFontDict = nil;


CTFontRef FontFromBundle(NSString *fontName, CGFloat height)
{
    NSString *fontPath = [[NSBundle mainBundle] pathForResource:fontName.stringByDeletingPathExtension
                                                         ofType:fontName.pathExtension];
    if (!fontPath) {
        return NULL;
    }
    
    CGDataProviderRef dataProvider = CGDataProviderCreateWithFilename([fontPath UTF8String]);
    if (!dataProvider) {
        return NULL;
    }
    
    CGFontRef fontRef = CGFontCreateWithDataProvider(dataProvider);
    if (!fontRef) {
        CGDataProviderRelease(dataProvider);
        return NULL;
    }
    
    CTFontRef fontCore = CTFontCreateWithGraphicsFont(fontRef, height, NULL, NULL);
    CGDataProviderRelease(dataProvider);
    CGFontRelease(fontRef);
    
    return fontCore;
}

GLuint __CreateStringTexture(const std::string& str, TextureScaleMode scaleMode, const std::string& fontName, float fontSize, Vector2* imageSize, GLushort *resizedWidth, GLushort *resizedHeight)
{
    GLuint ret = GL_INVALID_VALUE;
    
    // テキスト描画に必要なオブジェクトを作成する
    NSString *fontNameObj = [[NSString alloc] initWithCString:fontName.c_str() encoding:NSUTF8StringEncoding];
    NSString *strObj = [[NSString alloc] initWithCString:str.c_str() encoding:NSUTF8StringEncoding];
    
    if (!sFontDict) {
        sFontDict = [[NSMutableDictionary alloc] init];
    }
    
    CTFontRef fontRef = NULL;
    NSFont *font;
    fontSize *= 2.0f;
    
    NSString *fontKey = [[NSString alloc] initWithFormat:@"%@-%.1f", fontNameObj, fontSize];
    font = [sFontDict objectForKey:fontKey];
    if (!font) {
        font = [NSFont fontWithName:fontNameObj size:fontSize];
        if (!font) {
            fontRef = FontFromBundle(fontNameObj, fontSize);
            font = (NSFont *)fontRef;
        }
        if (font) {
            [sFontDict setObject:font forKey:fontKey];
        } else {
            throw GameError("フォント \"%s\" が読み込めません。", fontName.c_str());
        }
    }
    NSDictionary *attrDict = [[NSDictionary alloc] initWithObjectsAndKeys:font, NSFontAttributeName,
                              [NSColor whiteColor], NSForegroundColorAttributeName, nil];

    NSSize size = [strObj sizeWithAttributes:attrDict];

    // 画像サイズの調整
    imageSize->x = size.width;
    imageSize->y = size.height;
    *resizedWidth = imageSize->x;
    *resizedHeight = imageSize->y;
    if ((*resizedWidth != 1) && (*resizedWidth & (*resizedWidth - 1))) {
        GLushort i = 1;
        while (i < *resizedWidth) {
            i *= 2;
        }
        *resizedWidth = i;
    }
    if ((*resizedHeight != 1) && (*resizedHeight & (*resizedHeight - 1))) {
        GLushort i = 1;
        while (i < *resizedHeight) {
            i *= 2;
        }
        *resizedHeight = i;
    }

    // メモリの確保とビットマップ画像の作成
    if (!sColorSpaceRef) {
        sColorSpaceRef = CGColorSpaceCreateDeviceRGB();
    }
    NSUInteger length = 4 * (int)(*resizedWidth) * (int)(*resizedHeight);
    if (!sBitmapData || sBitmapLength < length) {
        if (sBitmapData) {
            [sBitmapData release];
        }
        sBitmapLength = length;
        sBitmapData = [[NSMutableData alloc] initWithLength:sBitmapLength];
    }
    CGContextRef bitmapContextRef = CGBitmapContextCreate([sBitmapData mutableBytes],
                                                          (size_t)(*resizedWidth),
                                                          (size_t)(*resizedHeight),
                                                          8,                        // Bits per component
                                                          (size_t)(*resizedWidth) * 4, // Bytes per Row
                                                          sColorSpaceRef,
                                                          kCGImageAlphaPremultipliedLast);
    
    // ビットマップデータへの文字列の描画
    [NSGraphicsContext saveGraphicsState];
    [NSGraphicsContext setCurrentContext:[NSGraphicsContext graphicsContextWithCGContext:bitmapContextRef flipped:NO]];
    [[NSColor clearColor] setFill];
    NSRectFill(NSMakeRect(0, 0, *resizedWidth, *resizedHeight));
    [[NSColor whiteColor] set];
    [strObj drawAtPoint:NSMakePoint(0, 0) withAttributes:attrDict];
    [NSGraphicsContext restoreGraphicsState];

    // アルファ値に対する調整（これがないと半透明部分が黒くなってしまう）
    unsigned char* p = (unsigned char*)[sBitmapData mutableBytes];
    for (int i = 0; i < (*resizedWidth) * (*resizedHeight); i++) {
        float alpha = (float)*(p + 3) / 0xff;
        if (alpha > 0.0f && alpha < 1.0f) {
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p += 2;
        } else {
            p += 4;
        }
    }

    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);
    
    // ビットマップを割り当てる
    glPixelStorei(GL_UNPACK_ROW_LENGTH, (GLint)(*resizedWidth));            // テクスチャ画像の横幅
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                                  // テクスチャ画像はバイト単位で並んでいる
    
    if (scaleMode == TextureScaleModeLinear) {
        // 拡大・縮小時の線形補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        // 拡大・縮小時のニアレストネイバー補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // クランプ処理の指定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // テクスチャ画像データの設定
    glTexImage2D(GL_TEXTURE_2D,
                 0,                             // MIPMAPのレベル
                 GL_RGBA,                       // テクスチャで使うカラーコンポーネント数
                 (GLsizei)(*resizedWidth),      // テクスチャ画像の横幅
                 (GLsizei)(*resizedHeight),     // テクスチャ画像の高さ
                 0,                             // ボーダー（0:境界線なし、1:境界線あり）
                 GL_RGBA,                       // ビットマップの色の並び順
                 GL_UNSIGNED_BYTE,
                 [sBitmapData bytes]);

    // クリーンアップ
    [attrDict release];
    [strObj release];
    [fontNameObj release];
    CGContextRelease(bitmapContextRef);
    if (fontRef) {
        CFRelease(fontRef);
    }
    [fontKey release];
    
    return ret;
}


GLuint __LoadTexture(const std::string& imageNameCpp, TextureScaleMode scaleMode, Vector2* imageSize, GLushort* resizedWidth, GLushort* resizedHeight, bool& isFileExistingError)
{
    GLuint ret = GL_INVALID_VALUE;

    NSString *imageName = [[NSString alloc] initWithCString:imageNameCpp.c_str() encoding:NSUTF8StringEncoding];
    NSString *imageName2 = nil;

    BOOL isHiResImage = NO;

    if (__GMScaleFactor == 2.0f) {
        NSString *filename = [imageName stringByDeletingPathExtension];
        NSString *fileext = [imageName pathExtension];
        imageName2 = [[NSString alloc] initWithFormat:@"%@@2x.%@", filename, fileext];
    }

    // 画像の名前→画像のパス
    NSBundle* bundle = [NSBundle mainBundle];
    NSURL* imageURL = nil;
    if (imageName2) {
        imageURL = [bundle URLForImageResource:imageName2];
    }
    if (imageURL) {
        isHiResImage = YES;
        //printf("Loading texture image: %s\n", [[imageURL lastPathComponent] cStringUsingEncoding:NSUTF8StringEncoding]);
    } else {
        imageURL = [bundle URLForImageResource:imageName];
        isHiResImage = NO;
    }
    [imageName release];
    [imageName2 release];
    if (!imageURL) {
        isFileExistingError = YES;
        return ret;
    }
    isFileExistingError = NO;

    // 画像の読み込み
    CGImageSourceRef imageSourceRef = CGImageSourceCreateWithURL((CFURLRef)imageURL, NULL);
    CGImageRef imageRef = CGImageSourceCreateImageAtIndex(imageSourceRef, 0, NULL);
    if (imageRef == NULL) {
        CFRelease(imageSourceRef);
        return ret;
    }

    // 画像サイズの取得と調整
    imageSize->x = (float)CGImageGetWidth(imageRef);
    imageSize->y = (float)CGImageGetHeight(imageRef);
    *resizedWidth = imageSize->x;
    *resizedHeight = imageSize->y;
    if (isHiResImage) {
        imageSize->x /= 2;
        imageSize->y /= 2;
    }
    if ((*resizedWidth != 1) && (*resizedWidth & (*resizedWidth - 1))) {
        GLushort i = 1;
        while (i < *resizedWidth) {
            i *= 2;
        }
        *resizedWidth = i;
    }
    if ((*resizedHeight != 1) && (*resizedHeight & (*resizedHeight - 1))) {
        GLushort i = 1;
        while (i < *resizedHeight) {
            i *= 2;
        }
        *resizedHeight = i;
    }

    // ビットマップ（RGBAの並び）への変換
    if (!sColorSpaceRef) {
        sColorSpaceRef = CGColorSpaceCreateDeviceRGB();
    }
    NSUInteger length = 4 * (int)(*resizedWidth) * (int)(*resizedHeight);
    if (!sBitmapData || sBitmapLength < length) {
        if (sBitmapData) {
            [sBitmapData release];
        }
        sBitmapLength = length;
        sBitmapData = [[NSMutableData alloc] initWithLength:sBitmapLength];
    }
    CGContextRef bitmapContextRef = CGBitmapContextCreate([sBitmapData mutableBytes],
                                                          (size_t)(*resizedWidth),
                                                          (size_t)(*resizedHeight),
                                                          8,                        // Bits per component
                                                          (size_t)(*resizedWidth) * 4, // Bytes per Row
                                                          sColorSpaceRef,
                                                          kCGImageAlphaPremultipliedLast);
    CGContextClearRect(bitmapContextRef, CGRectMake(0, 0, (int)imageSize->x, (int)imageSize->y));
    CGContextDrawImage(bitmapContextRef,
                       CGRectMake(0, 0, (int)imageSize->x, (int)imageSize->y),
                       imageRef);

    //CGImageRef testImageRef = CGBitmapContextCreateImage(bitmapContextRef);
    //printf("%p\n", testImageRef);

    // アルファ値に対する調整（これがないと半透明部分が黒くなってしまう）
    unsigned char* p = (unsigned char*)[sBitmapData mutableBytes];
    for (int i = 0; i < (*resizedWidth) * (*resizedHeight); i++) {
        float alpha = (float)*(p + 3) / 0xff;
        if (alpha > 0.0f && alpha < 1.0f) {
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p += 2;
        } else {
            p += 4;
        }
    }

    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);

    // ビットマップを割り当てる
    glPixelStorei(GL_UNPACK_ROW_LENGTH, (GLint)(*resizedWidth));            // テクスチャ画像の横幅
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                                  // テクスチャ画像はバイト単位で並んでいる

    if (scaleMode == TextureScaleModeLinear) {
        // 拡大・縮小時の線形補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        // 拡大・縮小時のニアレストネイバー補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // クランプ処理の指定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // テクスチャ画像データの設定
    glTexImage2D(GL_TEXTURE_2D,
                 0,                             // MIPMAPのレベル
                 GL_RGBA,                       // テクスチャで使うカラーコンポーネント数
                 (GLsizei)(*resizedWidth),      // テクスチャ画像の横幅
                 (GLsizei)(*resizedHeight),     // テクスチャ画像の高さ
                 0,                             // ボーダー（0:境界線なし、1:境界線あり）
                 GL_RGBA,                       // ビットマップの色の並び順
                 GL_UNSIGNED_BYTE,
                 [sBitmapData bytes]);

    ///// クリーンアップ
    CGContextRelease(bitmapContextRef);
    CGImageRelease(imageRef);
    CFRelease(imageSourceRef);
    
    return ret;
}

