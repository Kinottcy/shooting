//
//  BaseRenderer.cpp
//  Game Framework
//
//  Created by numata on July 03, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "BaseRenderer.hpp"
#include "DrawBatch.hpp"
#include "Settings.hpp"
#include "Globals.hpp"


static bool CompareDrawDataBackToFront(DrawData* first, DrawData* second)
{
    if (first->layerDepth != second->layerDepth) {
        return (first->layerDepth < second->layerDepth);
    }
    if (first->drawCount != second->drawCount) {
        return (first->drawCount < second->drawCount);
    }
    if (first->blendMode != second->blendMode) {
        return (first->blendMode < second->blendMode);
    }

    int firstTextureName = 0;
    int secondTextureName = 0;
    if (first->texture) {
        firstTextureName = first->texture->GetName();
    }
    if (second->texture) {
        secondTextureName = second->texture->GetName();
    }
    if (firstTextureName > secondTextureName) {
        return false;
    }
    return true;
}


DrawData::DrawData(int _drawCount, DrawDataType _type, BlendMode _blendMode, float _layerDepth)
{
    drawCount = _drawCount;
    type = _type;
    layerDepth = _layerDepth;
    texture = NULL;
    blendMode = _blendMode;
    c0 = Color::white;
}

BaseRenderer::BaseRenderer()
{
    // Do nothing
}

BaseRenderer::~BaseRenderer()
{
    for (DrawData *data : mDataList) {
        delete data;
    }
}

void BaseRenderer::Start()
{
    mDrawCount = 0;
}

void BaseRenderer::End()
{
    // 描画コマンドの発行
    /*printf("SORT-BEFORE\n");
    for (std::list<DrawData*>::iterator it = mDataList.begin(); it != mDataList.end(); it++) {
        printf("   layerDepth=%.1f, drawCount=%d\n", (*it)->layerDepth, (*it)->drawCount);
    }*/
    mDataList.sort(CompareDrawDataBackToFront);
    /*printf("SORT-AFTER\n");
    for (std::list<DrawData*>::iterator it = mDataList.begin(); it != mDataList.end(); it++) {
        printf("   layerDepth=%.1f, drawCount=%d\n", (*it)->layerDepth, (*it)->drawCount);
    }*/

    BlendMode blendMode = BlendModeNone;
    Texture *texture = 0;
    int drawCount = 0;
    glDisable(GL_TEXTURE_2D);
    auto it = mDataList.begin();
    while (it != mDataList.end()) {
        DrawData *data = *it;
        if (data->blendMode != blendMode || data->texture != texture) {
            if (drawCount > 0) {
                DrawBatch::End();
                drawCount = 0;
            }
        }
        if (drawCount == 0) {
            DrawBatch::Begin();
        }
        blendMode = data->blendMode;
        texture = data->texture;
        GL::SetBlendMode(blendMode);
        if (texture) {
            GL::EnableTexture(true);
            GL::SetTexture(texture);
        } else {
            GL::EnableTexture(false);
        }
        PublishDrawCommand(data);

        // FIXME: ここでフラッシュしなくても良いはずだが、最適化がうまく行っておらず、これがないとDrawTriangle()した直後のDrawLine()が反映されなくなる。
        DrawBatch::__FlushBatchDraws();
        drawCount++;
        it++;
    }
    if (drawCount > 0) {
        DrawBatch::End();
    }

    // 描画リストのクリア
    for (DrawData *data : mDataList) {
        delete data;
    }
    mDataList.clear();
}

void BaseRenderer::PublishDrawCommand(DrawData *data)
{
    if (data->type == DrawDataType_Sprite) {
        Texture *texture = data->texture;
        Vector2 texScale = texture->GetScale();
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0,
                            Vector2(0, 0), Vector2(texScale.x, 0),
                            texScale, Vector2(0, texScale.y));
    } else if (data->type == DrawDataType_Sprite_colors2) {
        Texture *texture = data->texture;
        Vector2 texScale = texture->GetScale();
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0, data->c0, data->c1, data->c1,
                            Vector2(0, 0), Vector2(texScale.x, 0),
                            texScale, Vector2(0, texScale.y));
    } else if (data->type == DrawDataType_Sprite_colors4) {
        Texture *texture = data->texture;
        Vector2 texScale = texture->GetScale();
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0, data->c1, data->c2, data->c3,
                            Vector2(0, 0), Vector2(texScale.x, 0),
                            texScale, Vector2(0, texScale.y));
    } else if (data->type == DrawDataType_Sprite_FromRect) {
        Texture *texture = data->texture;
        Vector2 texSize = texture->GetSize();
        const Rect& srcRect = data->srcRect;

        float tMinX = (srcRect.x / texSize.x) * texture->GetScale().x;
        float tMaxX = ((srcRect.x + srcRect.width) / texSize.x) * texture->GetScale().x;
        float tMinY = (srcRect.y / texSize.y) * texture->GetScale().y;
        float tMaxY = ((srcRect.y + srcRect.height) / texSize.y) * texture->GetScale().y;
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0,
                            Vector2(tMinX, tMinY), Vector2(tMaxX, tMinY),
                            Vector2(tMaxX, tMaxY), Vector2(tMinX, tMaxY));
    } else if (data->type == DrawDataType_Sprite_FromRect_colors2) {
        Texture *texture = data->texture;
        Vector2 texSize = texture->GetSize();
        const Rect& srcRect = data->srcRect;

        float tMinX = (srcRect.x / texSize.x) * texture->GetScale().x;
        float tMaxX = ((srcRect.x + srcRect.width) / texSize.x) * texture->GetScale().x;
        float tMinY = (srcRect.y / texSize.y) * texture->GetScale().y;
        float tMaxY = ((srcRect.y + srcRect.height) / texSize.y) * texture->GetScale().y;
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0, data->c0, data->c1, data->c1,
                            Vector2(tMinX, tMinY), Vector2(tMaxX, tMinY),
                            Vector2(tMaxX, tMaxY), Vector2(tMinX, tMaxY));
    } else if (data->type == DrawDataType_Sprite_FromRect_colors4) {
        Texture *texture = data->texture;
        Vector2 texSize = texture->GetSize();
        const Rect& srcRect = data->srcRect;

        float tMinX = (srcRect.x / texSize.x) * texture->GetScale().x;
        float tMaxX = ((srcRect.x + srcRect.width) / texSize.x) * texture->GetScale().x;
        float tMinY = (srcRect.y / texSize.y) * texture->GetScale().y;
        float tMaxY = ((srcRect.y + srcRect.height) / texSize.y) * texture->GetScale().y;
        DrawBatch::FillQuad(data->p0, data->p1, data->p2, data->p3,
                            data->c0, data->c1, data->c2, data->c3,
                            Vector2(tMinX, tMinY), Vector2(tMaxX, tMinY),
                            Vector2(tMaxX, tMaxY), Vector2(tMinX, tMaxY));
    } else if (data->type == DrawDataType_Line) {
        DrawBatch::DrawLine(data->p0, data->p1, data->c0, data->c1, data->lineWidth);
    } else if (data->type == DrawDataType_Triangle) {
        DrawBatch::FillTriangle(data->p0, data->p1, data->p2,
                                data->c0, data->c1, data->c2);
    } else {
        printf("SimpleDraw: Unknown draw command: type=%d\n", data->type);
    }
}

BlendMode BaseRenderer::GetBlendMode() const
{
    return mBlendMode;
}

void BaseRenderer::SetBlendMode(BlendMode blendMode)
{
    mBlendMode = blendMode;
}


#pragma mark - テクスチャの描画

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->texture = texture;
    data->c0 = color;

    mDataList.push_back(data);
}

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite_colors2, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->texture = texture;
    data->c0 = color1;
    data->c1 = color2;

    mDataList.push_back(data);
}

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite_colors4, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->texture = texture;
    data->c0 = color1;
    data->c1 = color2;
    data->c2 = color3;
    data->c3 = color4;

    mDataList.push_back(data);
}

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite_FromRect, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->srcRect = srcRect;
    data->texture = texture;
    data->c0 = color;

    mDataList.push_back(data);
}

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color1, const Color& color2)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite_FromRect_colors2, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->srcRect = srcRect;
    data->texture = texture;
    data->c0 = color1;
    data->c1 = color2;

    mDataList.push_back(data);
}

void BaseRenderer::DrawSprite(float layerDepth, Texture *texture, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, const Game::Rect& srcRect, const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Sprite_FromRect_colors4, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->p3 = p3;
    data->srcRect = srcRect;
    data->texture = texture;
    data->c0 = color1;
    data->c1 = color2;
    data->c2 = color3;
    data->c3 = color4;

    mDataList.push_back(data);
}


#pragma mark - 単純図形の描画

void BaseRenderer::DrawLine(float layerDepth, const Vector2& p0, const Vector2& p1, float width, const Color& c0, const Color& c1)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Line, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->c0 = c0;
    data->c1 = c1;
    data->lineWidth = width * __GMScaleFactor;

    mDataList.push_back(data);
}

void BaseRenderer::FillTriangle(
    float layerDepth, const Vector2& p0, const Vector2& p1, const Vector2& p2,
    const Color& c0, const Color& c1, const Color& c2)
{
    DrawData *data = new DrawData(mDrawCount++, DrawDataType_Triangle, mBlendMode, layerDepth);
    data->p0 = p0;
    data->p1 = p1;
    data->p2 = p2;
    data->c0 = c0;
    data->c1 = c1;
    data->c2 = c2;

    mDataList.push_back(data);
}

