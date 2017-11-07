//
//  Simple2D.cpp
//  Game Framework
//
//  Created by numata on Dec 4, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "Simple2D.hpp"
#include "Settings.hpp"
#include "Globals.hpp"

#include <algorithm>
#include <map>
#include <string>
#include <vector>


static int layerDepth = 0;

static Matrix4x4 viewRotationMatrix;
static Matrix4x4 viewScaleMatrix;
static Matrix4x4 viewTranslationMatrix;
static Matrix4x4 viewMatrix;

static Matrix4x4 worldRotationMatrix;
static Matrix4x4 worldScaleMatrix;
static Matrix4x4 worldTranslationMatrix;
static Matrix4x4 worldMatrix;

struct TextureUseInfo
{
    Texture *tex;
    bool    used;
    
    TextureUseInfo(Texture *t)
    {
        tex = t;
        used = true;
    }
};

static vector<string> printStrings;
static map<string, TextureUseInfo*> textTextureMap;
static string   textFontName;
static float    textFontSize;


void __InitSimple2D();
void __OutputPrintStrings();
void __InitTextFontInfo();
void __CleanUpTextTextures();

static void SetViewMatrices();
static void SetWorldMatrices();


static void __InitViewMatrices()
{
    viewRotationMatrix = Matrix4x4::identity;
    viewScaleMatrix = Matrix4x4::identity;
    viewTranslationMatrix = Matrix4x4::identity;

    Camera *camera = GMGame::GetInstance()->camera;
    Matrix4x4 baseTranslation = Matrix4x4::Translation(Screen::size() / 2);
    camera->SetViewMatrix(baseTranslation);

    SetViewMatrices();
}

static void __InitWorldMatrices()
{
    worldRotationMatrix = Matrix4x4::identity;
    worldScaleMatrix = Matrix4x4::identity;
    worldTranslationMatrix = Matrix4x4::identity;

    SetWorldMatrices();
}

void __InitSimple2D()
{
    __InitViewMatrices();
    SetViewMatrices();

    __InitWorldMatrices();
    SetWorldMatrices();

    SetBlendMode(BlendModeAlpha);
    SetLayer(0);
}


void Clear(const Color& color)
{
    Camera *camera = GMGame::GetInstance()->camera;
    camera->Clear(color);
}

void DrawCircle(const Vector2& center, float radius, const Color& color)
{
    DrawCircle(center, {radius, radius}, 1.0f, 0.0f, M_PI*2, color, color);
}

void DrawCircle(const Vector2& center, float radius, float width, const Color& color)
{
    DrawCircle(center, Vector2(radius, radius), width, 0.0f, M_PI*2, color, color);
}

void DrawCircle(const Vector2& center, float radius, float width, float startRad, float endRad, const Color& color)
{
    DrawCircle(center, {radius, radius}, width, startRad, endRad, color, color);
}

void DrawCircle(const Vector2& center, float radius, float width, float startRad, float endRad, const Color& startColor, const Color& endColor)
{
    DrawCircle(center, radius, width, startRad, endRad, startColor, endColor);
}

void DrawCircle(const Vector2& center, const Vector2& radius, const Color& color)
{
    DrawCircle(center, radius, 1.0f, 0.0f, M_PI * 2, color, color);
}

void DrawCircle(const Vector2& center, const Vector2& radius, float width, const Color& color)
{
    DrawCircle(center, radius, width, 0.0f, M_PI * 2, color, color);
}

void DrawCircle(const Vector2& center, const Vector2& radius, float width, float startRad, float endRad, const Color& color)
{
    DrawCircle(center, radius, width, startRad, endRad, color);
}

void DrawCircle(const Vector2& center, const Vector2& radius, float width, float startRad, float endRad, const Color& startColor, const Color& endColor)
{
    int divCount = 60*2;
    float maxR = std::max(radius.x, radius.y);
    if (maxR <= 10.0f) {
        divCount = 10*2;
    } else if (maxR <= 20.0f) {
        divCount = 18*2;
    } else if (maxR <= 50.0f) {
        divCount = 24*2;
    } else if (maxR <= 100.0f) {
        divCount = 30*2;
    } else if (maxR <= 200.0f) {
        divCount = 40*2;
    }

    while (endRad < startRad) {
        endRad += M_PI * 2;
    }

    Matrix4x4 vwMat = viewMatrix * worldMatrix;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    float oneAngle = M_PI * 2 / divCount;

    float angle = startRad;
    Vector2 oldPos;
    oldPos.x = center.x + cosf(angle) * radius.x;
    oldPos.y = center.y + sinf(angle) * radius.y;
    oldPos = vwMat * oldPos;
    while (angle <= endRad) {
        angle += oneAngle;
        float progress = (angle - startRad) / (endRad - startRad);
        Vector2 pos;
        pos.x = center.x + cosf(angle) * radius.x;
        pos.y = center.y + sinf(angle) * radius.y;
        pos = vwMat * pos;
        Color color = Color::Lerp(startColor, endColor, progress);
        renderer->DrawLine(layerDepth, oldPos, pos, width, color, color);
        oldPos = pos;
    }
}

void DrawLine(const Vector2& p1, const Vector2& p2, const Color& color)
{
    DrawLine(p1, p2, 1.0f, color, color);
}

void DrawLine(const Vector2& p1, const Vector2& p2, const Color& color1, const Color& color2)
{
    DrawLine(p1, p2, 1.0f, color1, color2);
}

void DrawLine(const Vector2& p1, const Vector2& p2, float width, const Color& color)
{
    DrawLine(p1, p2, width, color, color);
}

void DrawLine(const Vector2& p1, const Vector2& p2, float width, const Color& color1, const Color& color2)
{
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawLine(layerDepth, p1_2, p2_2, width, color1, color2);
}

void DrawPoint(const Vector2& pos, const Color& color)
{
    FillRect(Rect(pos.x, pos.y, 1, 1), color);
}

void DrawRect(const Game::Rect& rect, const Color& color)
{
    DrawRect(rect, 1.0f, color, color, color, color);
}

void DrawRect(const Game::Rect& rect, const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    DrawRect(rect, 1.0f, color1, color2, color3, color4);
}

void DrawRect(const Game::Rect& rect, float width, const Color& color)
{
    DrawRect(rect, width, color, color, color, color);
}

void DrawRect(const Game::Rect& rect, float width, const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    Vector2 p1 = rect.Min();
    Vector2 p4 = rect.Max();
    Vector2 p2(p4.x, p1.y);
    Vector2 p3(p1.x, p4.y);
    
    p1 = viewMatrix * worldMatrix * p1;
    p2 = viewMatrix * worldMatrix * p2;
    p3 = viewMatrix * worldMatrix * p3;
    p4 = viewMatrix * worldMatrix * p4;
    
    renderer->DrawLine(layerDepth, p1, p2, width, color1, color2);
    renderer->DrawLine(layerDepth, p2, p4, width, color2, color4);
    renderer->DrawLine(layerDepth, p4, p3, width, color4, color3);
    renderer->DrawLine(layerDepth, p3, p1, width, color3, color1);
}

void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color)
{
    DrawTriangle(p1, p2, p3, 1.0f, color, color, color);
}

void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3)
{
    DrawTriangle(p1, p2, p3, 1.0f, color1, color2, color3);
}

void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, float width, const Color& color)
{
    DrawTriangle(p1, p2, p3, width, color, color, color);
}

void DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, float width, const Color& color1, const Color& color2, const Color& color3)
{
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;
    
    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawLine(layerDepth, p1_2, p2_2, width, color1, color2);
    renderer->DrawLine(layerDepth, p2_2, p3_2, width, color2, color3);
    renderer->DrawLine(layerDepth, p3_2, p1_2, width, color3, color1);
}

static Texture *CreateTextTexture(const std::string& text)
{
    string strName = FormatString("%s-%.1f:%s", textFontName.c_str(), textFontSize, text.c_str());
    TextureUseInfo *texInfo = textTextureMap[strName];
    Texture *tex = 0;
    if (texInfo) {
        tex = texInfo->tex;
        texInfo->used = true;
    }
    if (!tex) {
        tex = new Texture(text, textFontName, textFontSize, TextureScaleModeLinear);
        textTextureMap[strName] = new TextureUseInfo(tex);
    }
    return tex;
}

Vector2 GetTextSize(const std::string& str)
{
    Texture *tex = CreateTextTexture(str);
    return tex->GetSize();
}

void SetFont(const std::string& fontName, float fontSize)
{
    textFontName = fontName;
    textFontSize = fontSize;
}

void DrawText(const std::string& str, const Vector2& pos, const Color& color)
{
    DrawText(str, pos, color, color);
}

void DrawText(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2)
{
    Texture *tex = CreateTextTexture(str);
    Vector2 texSize = tex->GetSize() / 2.0f;

    const Vector2 p0 = pos;
    const Vector2 p1 = pos + Vector2(texSize.x, 0);
    const Vector2 p2 = pos + texSize;
    const Vector2 p3 = pos + Vector2(0, texSize.y);

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color1, color2);
}

void DrawTextCenter(const std::string& str, const Vector2& pos, const Color& color)
{
    DrawTextCenter(str, pos, color, color);
}

void DrawTextCenter(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2)
{
    Texture *tex = CreateTextTexture(str);
    Vector2 texSize = tex->GetSize() / 2.0f;

    Vector2 center(texSize.x / 2, 0);

    const Vector2 p0 = pos - center;
    const Vector2 p1 = pos + Vector2(texSize.x, 0) - center;
    const Vector2 p2 = pos + texSize - center;
    const Vector2 p3 = pos + Vector2(0, texSize.y) - center;

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color1, color2);
}

void DrawTextRight(const std::string& str, const Vector2& pos, const Color& color)
{
    DrawTextRight(str, pos, color, color);
}

void DrawTextRight(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2)
{
    Texture *tex = CreateTextTexture(str);
    Vector2 texSize = tex->GetSize() / 2.0f;

    Vector2 theSize(texSize.x, 0);

    const Vector2 p0 = pos - theSize;
    const Vector2 p1 = pos + Vector2(texSize.x, 0) - theSize;
    const Vector2 p2 = pos + texSize - theSize;
    const Vector2 p3 = pos + Vector2(0, texSize.y) - theSize;

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color1, color2);
}

void DrawImage(const std::string& filename, const Rect& destRect)
{
    DrawImage(filename, destRect, Color::white);
}

void DrawImage(const std::string& filename, const Rect& destRect, const Color& color)
{
    __gGMLastErrorPlace = "DrawImage()";
    Texture *tex = GMGame::GetInstance()->LoadTexture(filename);
    Vector2 texSize = tex->GetSize();

    float aspectRatio = texSize.x / texSize.y;
    float screenRatio = (float)Screen::width / Screen::height;

    Vector2 p0, p1, p2, p3;
    if (screenRatio < aspectRatio) {
        // スクリーン比よりも横長
        float height = destRect.width * (1.0f /aspectRatio);
        p0 = destRect.Min() + Vector2(0, (Screen::height - height) / 2);
        p1 = p0 + Vector2(destRect.width, 0);
        p2 = p0 + Vector2(destRect.width, height);
        p3 = p0 + Vector2(0, height);
    } else {
        // スクリーン比よりも縦長
        float width = destRect.height * aspectRatio;
        p0 = destRect.Min() + Vector2((Screen::width - width) / 2, 0);
        p1 = p0 + Vector2(width, 0);
        p2 = p0 + Vector2(width, destRect.height);
        p3 = p0 + Vector2(0, destRect.height);
    }

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color);
}

void DrawImageFit(const std::string& filename, const Rect& destRect)
{
    DrawImageFit(filename, destRect, Color::white);
}

void DrawImageFit(const std::string& filename, const Rect& destRect, const Color& color)
{
    __gGMLastErrorPlace = "DrawImageFit()";
    Texture *tex = GMGame::GetInstance()->LoadTexture(filename);

    const Vector2 p0 = destRect.Min();
    const Vector2 p1 = p0 + Vector2(destRect.width, 0);
    const Vector2 p2 = p0 + Vector2(destRect.width, destRect.height);
    const Vector2 p3 = p0 + Vector2(0, destRect.height);

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color);
}

void DrawImage(const std::string& filename, const Vector2& pos)
{
    DrawImage(filename, pos, Vector2::zero, 0.0f, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center)
{
    DrawImage(filename, pos, center, 0.0f, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Color& color)
{
    DrawImage(filename, pos, Vector2::zero, 0.0f, color);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, const Color& color)
{
    DrawImage(filename, pos, center, 0.0f, color);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, float angle)
{
    DrawImage(filename, pos, center, angle, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, float angle, const Color& color)
{
    __gGMLastErrorPlace = "DrawImage()";
    Texture *tex = GMGame::GetInstance()->LoadTexture(filename);
    Vector2 texSize = tex->GetSize();

    const Vector2 p0 = -center;
    const Vector2 p1 = Vector2(texSize.x, 0) - center;
    const Vector2 p2 = texSize - center;
    const Vector2 p3 = Vector2(0, texSize.y) - center;

    Matrix4x4 mat = Matrix4x4::RotationZ(angle) * viewMatrix * worldMatrix * Matrix4x4::Translation(pos);
    Vector2 p0_2 = mat * p0;
    Vector2 p1_2 = mat * p1;
    Vector2 p2_2 = mat * p2;
    Vector2 p3_2 = mat * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, color);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect)
{
    DrawImage(filename, pos, srcRect, Vector2::zero, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Vector2& center)
{
    DrawImage(filename, pos, srcRect, center, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Color& color)
{
    DrawImage(filename, pos, srcRect, Vector2::zero, Color::white);
}

void DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Vector2& center, const Color& color)
{
    __gGMLastErrorPlace = "DrawImage()";
    const Vector2 p0 = pos - center;
    const Vector2 p1 = pos + Vector2(srcRect.width, 0) - center;
    const Vector2 p2 = pos + srcRect.Size() - center;
    const Vector2 p3 = pos + Vector2(0, srcRect.height) - center;

    Vector2 p0_2 = viewMatrix * worldMatrix * p0;
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    Texture *tex = GMGame::GetInstance()->LoadTexture(filename);
    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->DrawSprite(layerDepth, tex, p0_2, p1_2, p2_2, p3_2, srcRect, color);
}

Vector2 GetImageSize(const std::string& filename)
{
    __gGMLastErrorPlace = "GetImageSize()";
    Texture *tex = GMGame::GetInstance()->LoadTexture(filename);
    return tex->GetSize();
}

void FillCircle(const Vector2& center, float radius, const Color& color)
{
    FillCircle(center, {radius, radius}, 0.0f, M_PI * 2, color, color);
}

void FillCircle(const Vector2& center, float radius, float startRad, float endRad, const Color& color)
{
    FillCircle(center, {radius, radius}, startRad, endRad, color, color);
}

void FillCircle(const Vector2& center, float radius, float startRad, float endRad, const Color& startColor, const Color& endColor)
{
    FillCircle(center, {radius, radius}, startRad, endRad, startColor, endColor);
}

void FillCircle(const Vector2& center, const Vector2& radius, const Color& color)
{
    FillCircle(center, radius, 0.0f, M_PI * 2, color, color);
}

void FillCircle(const Vector2& center, const Vector2& radius, float startRad, float endRad, const Color& color)
{
    FillCircle(center, radius, startRad, endRad, color, color);
}

void FillCircle(const Vector2& center, const Vector2& radius, float startRad, float endRad, const Color& startColor, const Color& endColor)
{
    int divCount = 60*2;
    float maxR = std::max(radius.x, radius.y);
    if (maxR <= 10.0f) {
        divCount = 10*2;
    } else if (maxR <= 20.0f) {
        divCount = 18*2;
    } else if (maxR <= 50.0f) {
        divCount = 24*2;
    } else if (maxR <= 100.0f) {
        divCount = 30*2;
    } else if (maxR <= 200.0f) {
        divCount = 40*2;
    }

    while (endRad < startRad) {
        endRad += M_PI * 2;
    }

    Matrix4x4 vwMat = viewMatrix * worldMatrix;
    Vector2 center_2 = vwMat * center;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    float oneAngle = M_PI * 2 / divCount;

    float angle = startRad;
    Vector2 oldPos;
    oldPos.x = center.x + cosf(angle) * radius.x;
    oldPos.y = center.y + sinf(angle) * radius.y;
    oldPos = vwMat * oldPos;
    Color oldColor = startColor;
    while (angle < endRad) {
        angle += oneAngle;
        if (angle > endRad) {
            angle = endRad;
        }
        float progress = (angle - startRad) / (endRad - startRad);
        Vector2 pos;
        pos.x = center.x + cosf(angle) * radius.x;
        pos.y = center.y + sinf(angle) * radius.y;
        pos = vwMat * pos;
        Color color = Color::Lerp(startColor, endColor, progress);
        renderer->FillTriangle(layerDepth, oldPos, pos, center_2, oldColor, color, oldColor);
        oldColor = color;
        oldPos = pos;
    }
}

void FillRect(const Rect& rect, const Color& color)
{
    FillRect(rect, color, color, color, color);
}

void FillRect(const Rect& rect, const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    Vector2 p1 = rect.Min();
    Vector2 p4 = rect.Max();
    Vector2 p2(p4.x, p1.y);
    Vector2 p3(p1.x, p4.y);
    
    p1 = viewMatrix * worldMatrix * p1;
    p2 = viewMatrix * worldMatrix * p2;
    p3 = viewMatrix * worldMatrix * p3;
    p4 = viewMatrix * worldMatrix * p4;
    
    renderer->FillTriangle(layerDepth, p1, p2, p3, color1, color2, color3);
    renderer->FillTriangle(layerDepth, p2, p4, p3, color2, color4, color3);
}

void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color)
{
    FillTriangle(p1, p2, p3, color, color, color);
}

void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3)
{
    Vector2 p1_2 = viewMatrix * worldMatrix * p1;
    Vector2 p2_2 = viewMatrix * worldMatrix * p2;
    Vector2 p3_2 = viewMatrix * worldMatrix * p3;

    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->FillTriangle(layerDepth, p1_2, p2_2, p3_2, color1, color2, color3);
}


void SetBlendMode(BlendMode mode)
{
    BaseRenderer *renderer = GMGame::GetInstance()->renderer;
    renderer->End();
    renderer->SetBlendMode(mode);
    renderer->Start();
}

void SetLayer(int layer)
{
    layerDepth = layer;
}

static void SetViewMatrices()
{
    viewMatrix = viewRotationMatrix * viewScaleMatrix * viewTranslationMatrix;
}

void SetCameraRotation(float rad)
{
    viewRotationMatrix = Matrix4x4::RotationZ(rad).Inverse();
    SetViewMatrices();
}

void SetCameraScale(float scale)
{
    SetCameraScale(scale, scale);
}

void SetCameraScale(float x, float y)
{
    SetCameraScale(Vector2(x, y));
}

void SetCameraScale(const Vector2& vec)
{
    viewScaleMatrix = Matrix4x4::Scale(vec);
    SetViewMatrices();
}

void SetCameraTranslation(float x, float y)
{
    SetCameraTranslation(Vector2(x, y));
}

void SetCameraTranslation(const Vector2& vec)
{
    viewTranslationMatrix = Matrix4x4::Translation(vec).Inverse();
    SetViewMatrices();
}

void SetCameraTRS(const Vector2& pos, float rad, float scale)
{
    SetCameraTRS(pos, rad, Vector2(scale, scale));
}

void SetCameraTRS(const Vector2& pos, float rad, const Vector2& scale)
{
    viewRotationMatrix = Matrix4x4::RotationZ(rad).Inverse();
    viewScaleMatrix = Matrix4x4::Scale(scale);
    viewTranslationMatrix = Matrix4x4::Translation(pos).Inverse();
    SetViewMatrices();
}

void ResetCameraTRS()
{
    __InitViewMatrices();
    SetViewMatrices();
}

static void SetWorldMatrices()
{
    worldMatrix = worldRotationMatrix * worldScaleMatrix * worldTranslationMatrix;
}

void SetModelRotation(float rad)
{
    worldRotationMatrix = Matrix4x4::RotationZ(rad);
    SetWorldMatrices();
}

void SetModelScale(float scale)
{
    SetModelScale(Vector2(scale, scale));
}

void SetModelScale(float x, float y)
{
    SetModelScale(Vector2(x, y));
}

void SetModelScale(const Vector2& scale)
{
    worldScaleMatrix = Matrix4x4::Scale(scale);
    SetWorldMatrices();
}

void SetModelTranslation(float x, float y)
{
    SetModelTranslation(Vector2(x, y));
}

void SetModelTranslation(const Vector2& vec)
{
    worldTranslationMatrix = Matrix4x4::Translation(vec);
    SetWorldMatrices();
}

void SetModelTRS(const Vector2& pos, float rad, float scale)
{
    SetModelTRS(pos, rad, Vector2(scale, scale));
}

void SetModelTRS(const Vector2& pos, float rad, const Vector2& scale)
{
    worldRotationMatrix = Matrix4x4::RotationZ(rad);
    worldScaleMatrix = Matrix4x4::Scale(scale);
    worldTranslationMatrix = Matrix4x4::Translation(pos);
    SetWorldMatrices();
}

void ResetModelTRS()
{
    __InitWorldMatrices();
    SetWorldMatrices();
}

/*!
    マウス位置の取得
 */
Vector2 GetMousePosition()
{
    Vector2 pos = Input::MousePosition();

    Matrix4x4 baseTranslation = Matrix4x4::Translation(Screen::size() / 2);
    Matrix4x4 viewMat = viewRotationMatrix * viewScaleMatrix * viewTranslationMatrix * baseTranslation;

    return viewMat.Inverse() * pos;
}

Rect GetScreenBounds()
{
    Vector2 p0(-Screen::width/2, -Screen::height/2);
    Vector2 p1(Screen::width/2, Screen::height/2);
//    p0 = viewMatrix * worldMatrix * p0;
//    p1 = viewMatrix * worldMatrix * p1;
    Vector2 min = Vector2::Min(p0, p1);
    Vector2 max = Vector2::Max(p0, p1);
    return Rect(min.x, min.y, max.x - min.x, max.y - min.y);
}

void Debug()
{
    printStrings.push_back("");
}

void Debug(const char* format, ...)
{
    static char buffer[1024];
    va_list marker;
    va_start(marker,format);
    vsprintf(buffer, format, marker);
    va_end(marker);

    printStrings.push_back(buffer);
}

static void DrawPrintText(const Vector2& pos, const std::string& str)
{
    DrawText(str, pos+Vector2(2, -3), Color::black.Alpha(0.5f));
    DrawText(str, pos+Vector2(1, -2), Color::white);
    DrawText(str, pos, Color(0x1e/255.0f, 0x90/255.0f, 1.0f));
}

void __OutputPrintStrings()
{
    Matrix4x4 oldViewMatrix = viewMatrix;
    Matrix4x4 oldWorldMatrix = worldMatrix;

    ResetCameraTRS();
    ResetModelTRS();
    SetBlendMode(BlendModeAlpha);

    SetFont("Menlo-Bold", 20.0f);
    float fontHeight = 25.0f;

    float y = Screen::height / 2 - fontHeight;
    for (auto str : printStrings) {
        DrawPrintText(Vector2(-Screen::width/2 + 4, y), str);
        y -= fontHeight;
    }
    printStrings.clear();

    viewMatrix = oldViewMatrix;
    worldMatrix = oldWorldMatrix;
}

void __InitTextFontInfo()
{
    SetFont("Helvetica-Bold", 20.0f);

    for (auto& kv : textTextureMap) {
        kv.second->used = false;
    }
}

void __CleanUpTextTextures()
{
    auto it = textTextureMap.begin();
    while (it != textTextureMap.end()) {
        TextureUseInfo *texInfo = (*it).second;
        if (texInfo->used) {
            it++;
        } else {
            delete texInfo->tex;
            delete texInfo;
            it = textTextureMap.erase(it);
        }
    }
}

