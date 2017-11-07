//
//  Texture.mm
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "Texture.hpp"
#include "GameError.hpp"
#include "StringSupport.hpp"


static GLuint __CreateTexture(int width, int height, TextureFormat format)
{
    GLuint ret = GL_INVALID_VALUE;
    
    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    
    // エラーチェック
    if (ret == GL_INVALID_OPERATION) {
        throw GameInvalidOperationError("テクスチャの生成に失敗しました。(INVALID_OPERATION).");
    }
    else if (ret == GL_INVALID_VALUE) {
        throw GameError("テクスチャの生成に失敗しました。(INVALID_VALUE).");
    }
    else if (ret == GL_INVALID_ENUM) {
        throw GameError("テクスチャの生成に失敗しました。(INVALID_ENUM).");
    }

    // テクスチャ作成の実作業
    glBindTexture(GL_TEXTURE_2D, ret);

    GLint internalFormat = GL_RGBA;
    GLenum theFormat = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;

    if (format == TextureFormat_A8) {
        internalFormat = GL_ALPHA;
        theFormat = GL_ALPHA;
        type = GL_UNSIGNED_BYTE;
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,                 // MIPMAPレベル
                 internalFormat,    // テクスチャで使うコンポーネント数
                 (GLsizei)width, (GLsizei)height,   // テクスチャのサイズ
                 0,                 // ボーダー（0:境界線なし、1:境界線あり）
                 theFormat,         // ビットマップの色の並び順
                 type,              // 各コンポーネントのサイズ
                 0);

    return ret;
}

Texture::Texture(int width, int height)
{
    mTexName = __CreateTexture(width, height, TextureFormat_RGBA8);
    mImageSize = Vector2(width, height);
    mImageScale = Vector2::one;
}

Texture::Texture(int width, int height, TextureFormat format)
{
    mTexName = __CreateTexture(width, height, format);
    mImageSize = Vector2(width, height);
    mImageScale = Vector2::one;
}

Texture::Texture(const std::string& imageName, TextureScaleMode scaleMode)
{
    GLushort resizedWidth;
    GLushort resizedHeight;
    mFileName = imageName;
    
    bool isFileExistingError;
    mTexName = __LoadTexture(imageName, scaleMode, &mImageSize, &resizedWidth, &resizedHeight, isFileExistingError);
    if (mTexName == GL_INVALID_VALUE) {
        if (isFileExistingError) {
            throw GameError("テクスチャファイル \"%s\" が見つかりません。ファイル名およびファイル形式を確認してください。", imageName.c_str());
        } else {
            throw GameError("テクスチャファイル \"%s\" が読み込めません。ファイル形式を確認してください。", imageName.c_str());
        }
    }
    mImageScale.x = mImageSize.x / (float)resizedWidth;
    mImageScale.y = mImageSize.y / (float)resizedHeight;
}

Texture::Texture(const std::string& text, const std::string& fontName, float fontSize, TextureScaleMode scaleMode)
{
    GLushort resizedWidth;
    GLushort resizedHeight;

    mTexName = __CreateStringTexture(text, scaleMode, fontName, fontSize, &mImageSize, &resizedWidth, &resizedHeight);
    if (mTexName == GL_INVALID_VALUE) {
        throw GameError("文字列テクスチャの生成に失敗しました。文字列: \"%s\", フォント名: \"%s\", フォントサイズ: %.1f", text.c_str(), fontName.c_str(), fontSize);
    }
    mImageScale.x = mImageSize.x / (float)resizedWidth;
    mImageScale.y = mImageSize.y / (float)resizedHeight;
}

Texture::~Texture()
{
    if (mTexName != GL_INVALID_VALUE) {
        glDeleteTextures(1, &mTexName);
        mTexName = GL_INVALID_VALUE;
    }
}

Vector2 Texture::GetSize() const
{
    return mImageSize;
}

Vector2 Texture::GetScale() const
{
    return mImageScale;
}

void Texture::SetScale(const Vector2& scale)
{
    mImageScale = scale;
}

GLuint Texture::GetName() const
{
    return mTexName;
}

std::string Texture::GetFileName() const
{
    return mFileName;
}

std::string Texture::ToString() const
{
    return FormatString("Texture(size=%dx%d, scale=%.2fx%0.2f)", (int)mImageSize.x, (int)mImageSize.y, mImageScale.x, mImageScale.y);
}

