//
//  BaseRenderer.hpp
//  Game Framework
//
//  Created by numata on July 03, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __BASE_RENDERER_HPP__
#define __BASE_RENDERER_HPP__


#include "GL_class.hpp"
#include <list>


enum DrawDataType {
    DrawDataType_Sprite,
    DrawDataType_Sprite_colors2,
    DrawDataType_Sprite_colors4,
    DrawDataType_Sprite_FromRect,
    DrawDataType_Sprite_FromRect_colors2,
    DrawDataType_Sprite_FromRect_colors4,

    DrawDataType_Line,
    DrawDataType_Triangle,
};


struct DrawData
{
    DrawDataType    type;
    int             drawCount;
    float           layerDepth;
    BlendMode       blendMode;

    Vector2         p0;
    Vector2         p1;
    Vector2         p2;
    Color           c0;
    Color           c1;
    Color           c2;
    Color           c3;
    Game::Rect      srcRect;
    union {
        Vector2     p3;
        float       lineWidth;
    };

    Texture*        texture;

    DrawData(int drawCount, DrawDataType type, BlendMode blendMode, float layerDepth);
};


class BaseRenderer
{
    std::list<DrawData*>    mDataList;
    BlendMode               mBlendMode;
    int                     mDrawCount;

public:
    BaseRenderer();
    ~BaseRenderer();
    
public:
    void    Start();
    void    End();
    
public:
    BlendMode   GetBlendMode() const;
    void        SetBlendMode(BlendMode blendMode);
    
public:
    // スプライトの描画
    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color);
    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2);
    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3, const Color& color4);

    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color);
    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color1, const Color& color2);
    void    DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color1, const Color& color2, const Color& color3, const Color& color4);

    // 単純図形の描画
    void    DrawLine(float layerDepth, const Vector2& p0, const Vector2& p1, float width, const Color& c0, const Color& c1);
    void    FillTriangle(float layerDepth, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Color& c0, const Color& c1, const Color& c2);

private:
    void    PublishDrawCommand(DrawData *drawData);
    
};


#endif  //#ifndef __BASE_RENDERER_HPP__


