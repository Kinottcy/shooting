//
//  Texture.hpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include <OpenGL/OpenGL.h>
#include "GMObject.hpp"
#include "Color.hpp"
#include "Types.hpp"
#include "GameError.hpp"
#include <string>
#include "TextureLoader.hpp"


/*!
    @enum   TextureFormat
    @group  Graphics
 
    @constant   TextureFormat_RGBA8       各チャンネルに 8bit ずつ使用する、32bit RGBA ピクセルフォーマットです (unsigned byte)。
    @constant   TextureFormat_A8          8bit のアルファチャンネルのみのピクセルフォーマットです (unsigned byte)。
 */
enum TextureFormat
{
    TextureFormat_RGBA8,
    TextureFormat_A8,
};



/*!
    @class  Texture
    @group  Graphics
    <p>2次元のテクスチャを表現するためのクラスです。</p>
    <p>このクラスは、テクスチャの直接の描画はサポートしません。</p>
 */
class Texture : public GMObject
{
    std::string mFileName;
    GLuint      mTexName;
    Vector2     mImageSize;
    Vector2     mImageScale;

public:
#pragma mark - コンストラクタ
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     Texture
        @abstract   幅と高さを指定して、32bit ARGB フォーマットのテクスチャを作成します。
        幅と高さには、2の乗数しか指定できません。
     */
    Texture(int width, int height);

    /*!
        @method     Texture
        @abstract   幅と高さを指定して、指定されたフォーマットのテクスチャを作成します。
        幅と高さには、2の乗数しか指定できません。
     */
    Texture(int width, int height, TextureFormat format);

    /*!
        @method     Texture
        @abstract   画像ファイルの名前を指定してテクスチャを作成します。
        第2引数に TextureScaleModeLinear か TextureScaleModeNearest を指定することで、拡大・縮小時の補完方法を指定することができます。
     */
    Texture(const std::string& imageName, TextureScaleMode scaleMode = TextureScaleModeNearest);

    Texture(const std::string& text, const std::string& fontName, float fontSize, TextureScaleMode scaleMode = TextureScaleModeNearest);

    virtual ~Texture();

public:
#pragma mark - Public 関数
    /*!
        @task   Public 関数
     */

    std::string GetFileName() const;

    GLuint      GetName() const;

    /*!
        @method     GetSize
        @abstract   テクスチャのサイズをピクセル単位で取得します。
     */
    Vector2     GetSize() const;

    Vector2     GetScale() const;
    void        SetScale(const Vector2& scale);

    std::string ToString() const override;

};


#endif  //#ifndef __TEXTURE_HPP__


