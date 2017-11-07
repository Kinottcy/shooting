//
//  Simple2D.hpp
//  Game Framework
//
//  Created by numata on Dec 4, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __SIMPLE_2D_HPP__
#define __SIMPLE_2D_HPP__


#include "GameFramework.hpp"


// ゲーム画面のクリア（ビューの描画開始時のみ有効）
void    Clear(const Color& color);

// 単純図形の描画
void    DrawCircle(const Vector2& center, float radius, const Color& color);
void    DrawCircle(const Vector2& center, float radius, float width, const Color& color);
void    DrawCircle(const Vector2& center, float radius, float width, float startRad, float endRad, const Color& color);
void    DrawCircle(const Vector2& center, float radius, float width, float startRad, float endRad, const Color& startColor, const Color& endColor);
void    DrawCircle(const Vector2& center, const Vector2& radius, const Color& color);
void    DrawCircle(const Vector2& center, const Vector2& radius, float width, const Color& color);
void    DrawCircle(const Vector2& center, const Vector2& radius, float width, float startRad, float endRad, const Color& color);
void    DrawCircle(const Vector2& center, const Vector2& radius, float width, float startRad, float endRad, const Color& startColor, const Color& endColor);
void    DrawLine(const Vector2& p1, const Vector2& p2, const Color& color);
void    DrawLine(const Vector2& p1, const Vector2& p2, const Color& color1, const Color& color2);
void    DrawLine(const Vector2& p1, const Vector2& p2, float width, const Color& color);
void    DrawLine(const Vector2& p1, const Vector2& p2, float width, const Color& color1, const Color& color2);
void    DrawPoint(const Vector2& pos, const Color& color);
void    DrawRect(const Game::Rect& rect, const Color& color);
void    DrawRect(const Game::Rect& rect, const Color& color1, const Color& color2, const Color& color3, const Color& color4);
void    DrawRect(const Game::Rect& rect, float width, const Color& color);
void    DrawRect(const Game::Rect& rect, float width, const Color& color1, const Color& color2, const Color& color3, const Color& color4);
void    DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color);
void    DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3);
void    DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, float width, const Color& color);
void    DrawTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, float width, const Color& color1, const Color& color2, const Color& color3);

// 単純図形の塗りつぶし
void    FillCircle(const Vector2& center, float radius, const Color& color);
void    FillCircle(const Vector2& center, float radius, float startRad, float endRad, const Color& color);
void    FillCircle(const Vector2& center, float radius, float startRad, float endRad, const Color& startColor, const Color& endColor);
void    FillCircle(const Vector2& center, const Vector2& radius, const Color& color);
void    FillCircle(const Vector2& center, const Vector2& radius, float startRad, float endRad, const Color& color);
void    FillCircle(const Vector2& center, const Vector2& radius, float startRad, float endRad, const Color& startColor, const Color& endColor);
void    FillRect(const Game::Rect& rect, const Color& color);
void    FillRect(const Game::Rect& rect, const Color& color1, const Color& color2, const Color& color3, const Color& color4);
void    FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color);
void    FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color1, const Color& color2, const Color& color3);

// テキストの描画
Vector2 GetTextSize(const std::string& str);
void    SetFont(const std::string& fontName, float fontSize);
void    DrawText(const std::string& str, const Vector2& pos, const Color& color);
void    DrawText(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2);
void    DrawTextCenter(const std::string& str, const Vector2& pos, const Color& color);
void    DrawTextCenter(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2);
void    DrawTextRight(const std::string& str, const Vector2& pos, const Color& color);
void    DrawTextRight(const std::string& str, const Vector2& pos, const Color& color1, const Color& color2);

// 画像の描画
void    DrawImage(const std::string& filename, const Rect& destRect);
void    DrawImage(const std::string& filename, const Rect& destRect, const Color& color);
void    DrawImageFit(const std::string& filename, const Rect& destRect);
void    DrawImageFit(const std::string& filename, const Rect& destRect, const Color& color);

void    DrawImage(const std::string& filename, const Vector2& pos);
void    DrawImage(const std::string& filename, const Vector2& pos, const Color& color);
void    DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center);
void    DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, const Color& color);
void    DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, float angle);
void    DrawImage(const std::string& filename, const Vector2& pos, const Vector2& center, float angle, const Color& color);

void    DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect);
void    DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Color& color);
void    DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Vector2& center);
void    DrawImage(const std::string& filename, const Vector2& pos, const Game::Rect& srcRect, const Vector2& center, const Color& color);
Vector2 GetImageSize(const std::string& filename);

// 細かい調整を行うための関数
void    SetBlendMode(BlendMode mode);
void    SetLayer(int layer);

// ビュー行列（カメラ位置）の設定
void    SetCameraRotation(float rad);
void    SetCameraScale(float scale);
void    SetCameraScale(float x, float y);
void    SetCameraScale(const Vector2& vec);
void    SetCameraTranslation(float x, float y);
void    SetCameraTranslation(const Vector2& vec);
void    SetCameraTRS(const Vector2& pos, float rad, float scale);
void    SetCameraTRS(const Vector2& pos, float rad, const Vector2& scale);
void    ResetCameraTRS();

// モデル行列の設定
void    SetModelRotation(float rad);
void    SetModelScale(float scale);
void    SetModelScale(float x, float y);
void    SetModelScale(const Vector2& scale);
void    SetModelTranslation(float x, float y);
void    SetModelTranslation(const Vector2& vec);
void    SetModelTRS(const Vector2& pos, float rad, float scale);
void    SetModelTRS(const Vector2& pos, float rad, const Vector2& scale);
void    ResetModelTRS();

/*!
    @func GetMousePotision
    マウスの現在位置をリターンします。座標位置は、カメラ位置とモデル位置が考慮されます。
 */
Vector2 GetMousePosition();

/*!
    @func GetScreenBounds
    画面枠を表すRect構造体をリターンします。
 */
Rect GetScreenBounds();

// デバッグのサポート
void    Debug();
void    Debug(const char* format, ...);


#endif  //#ifndef __SIMPLE_2D_HPP__

