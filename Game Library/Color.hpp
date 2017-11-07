//
//  Color.hpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "GMObject.hpp"


struct Vector3;
struct Vector4;

/*!
    @class      Color
    @group      Graphics
    @abstract   ゲームで使用される色を表現するためのクラスです。
 */
struct Color : public GMObject
{
public:
#pragma mark - Static 変数
    /*!
        @const black
        @unity-compatible   true
        RGBAが(0, 0, 0, 1)の黒を表す色の定数です。
     */
    static const Color&   black;

    /*!
        @const blue
        @unity-compatible   true
        RGBAが(0, 0, 1, 1)の青を表す色の定数です。
     */
    static const Color&   blue;
    
    /*!
        @const clear
        @unity-compatible   true
        RGBAが(0, 0, 0, 0)の透明色を表す色の定数です。
     */
    static const Color&   clear;

    /*!
        @const cyan
        @unity-compatible   true
        RGBAが(0, 1, 1, 1)のシアンを表す色の定数です。
     */
    static const Color&   cyan;

    /*!
        @const darkblue
        @unity-compatible   true
        RGBAが(0, 0, 0.7, 1)の暗い青を表す色の定数です。
     */
    static const Color&   darkblue;

    /*!
        @const darkcyan
        @unity-compatible   true
        RGBAが(0, 0.5, 0.5, 1)の暗いシアンを表す色の定数です。
     */
    static const Color&   darkcyan;

    /*!
        @const darkgray
        @unity-compatible   true
        RGBAが(0.25, 0.25, 0.25, 1)の暗いグレーを表す色の定数です。
     */
    static const Color&   darkgray;

    /*!
        @const darkgreen
        @unity-compatible   true
        RGBAが(0, 0, 0.5, 1)の暗い青を表す色の定数です。
     */
    static const Color&   darkgreen;

    /*!
        @const darkorange
        @unity-compatible   true
        RGBAが(0.5, 0.25, 0, 1)の暗いオレンジを表す色の定数です。
     */
    static const Color&   darkorange;

    /*!
        @const darkpink
        @unity-compatible   true
        RGBAが(0.6, 0.08, 0.3, 1)の暗いピンクを表す色の定数です。
     */
    static const Color&   darkpink;

    /*!
        @const darkpurple
        @unity-compatible   true
        RGBAが(0.5, 0, 0.5, 1)の暗い紫を表す色の定数です。
     */
    static const Color&   darkpurple;

    /*!
        @const darkred
        @unity-compatible   true
        RGBAが(0.6, 0, 0, 1.0)の暗い赤を表す色の定数です。
     */
    static const Color&   darkred;

    /*!
        @const darkyellow
        @unity-compatible   true
        RGBAが(0.5, 0.5, 0, 1)の暗い黄色を表す色の定数です。
     */
    static const Color&   darkyellow;

    /*!
        @const gray
        @unity-compatible   true
        RGBAが(0.5, 0.5, 0.5, 1)のグレーを表す色の定数です。
     */
 	static const Color&   gray;

    /*!
        @const green
        @unity-compatible   true
        RGBAが(0, 1, 0, 1)の緑を表す色の定数です。
     */
 	static const Color&   green;

    /*!
        @const lightblue
        @unity-compatible   true
        RGBAが(0.5, 0.5, 1, 1)の明るい青を表す色の定数です。
     */
    static const Color&   lightblue;

    /*!
        @const lightcyan
        @unity-compatible   true
        RGBAが(0.65, 1, 1, 1)の明るいシアンを表す色の定数です。
     */
    static const Color&   lightcyan;

    /*!
        @const lightgray
        @unity-compatible   true
        RGBAが(0.75, 0.75, 0.75, 1)の明るいグレーを表す色の定数です。
     */
    static const Color&   lightgray;

    /*!
        @const lightgreen
        @unity-compatible   true
        RGBAが(0.5, 1, 0.5, 1)の明るい緑を表す色の定数です。
     */
    static const Color&   lightgreen;

    /*!
        @const lightorange
        @unity-compatible   true
        RGBAが(1, 0.75, 0.5, 1)の明るいオレンジを表す色の定数です。
     */
    static const Color&   lightorange;

    /*!
        @const lightpink
        @unity-compatible   true
        RGBAが(1, 0.5, 0.8, 1)の明るいピンクを表す色の定数です。
     */
    static const Color&   lightpink;

    /*!
        @const lightpurple
        @unity-compatible   true
        RGBAが(1, 0.5, 1, 1)の明るい紫を表す色の定数です。
     */
    static const Color&   lightpurple;

    /*!
        @const lightred
        @unity-compatible   true
        RGBAが(1, 0.5, 0.5, 1)の明るい赤を表す色の定数です。
     */
    static const Color&   lightred;

    /*!
        @const lightyellow
        @unity-compatible   true
        RGBAが(1, 1, 0.65, 1)の明るい黄色を表す色の定数です。
     */
    static const Color&   lightyellow;

    /*!
        @const orange
        @unity-compatible   true
        RGBAが(1, 0.5, 0, 1)のオレンジを表す色の定数です。
     */
    static const Color&     orange;

    /*!
        @const pink
        @unity-compatible   true
        RGBAが(1, 0.25, 0.6, 1)のピンクを表す色の定数です。
     */
    static const Color&     pink;

    /*!
        @const purple
        @unity-compatible   true
        RGBAが(1, 0, 1, 1)の紫を表す色の定数です。
     */
    static const Color&     purple;

    /*!
        @const red
        @unity-compatible   true
        RGBAが(1, 0, 0, 1)の赤を表す色の定数です。
     */
    static const Color&   red;

    /*!
        @const white
        @unity-compatible   true
        RGBAが(1, 1, 1, 1)の白を表す色の定数です。
     */
    static const Color&   white;

    /*!
        @const yellow
        @unity-compatible   true
        RGBAが(1, 1, 0, 1)の黄色を表す色の定数です。
     */
    static const Color&   yellow;


public:
#pragma mark - Static 関数
    /*!
        @task   Static 関数
     */

    /*!
        @method     EaseIn
        @abstract   2つの色の間を Ease In 補間した色を作成します。
     */
    static Color    EaseIn(const Color& a, const Color& b, float t);
    
    /*!
        @method     EaseInOut
        @abstract   2つの色の間を Ease In Out 補間した色を作成します。
     */
    static Color    EaseInOut(const Color& a, const Color& b, float t);

    /*!
        @method     EaseOut
        @abstract   2つの色の間を Ease Out 補間した色を作成します。
     */
    static Color    EaseOut(const Color& a, const Color& b, float t);

    /*!
        @method     HSVToRGB
        @unity-compatible   true
        HSV 色空間の値から RGB 色空間の色を作成します。
     */
    static Color    HSVToRGB(float H, float S, float V);

    /*!
        @method     HSVToRGB
        @unity-compatible   true
        HSV 色空間の値から RGB 色空間の色を作成します。
        hdr フラグが true の場合、各色要素は 0.0〜1.0 の範囲にクランプされません。
     */
    static Color    HSVToRGB(float H, float S, float V, bool hdr);

    /*!
        @method     Lerp
        @unity-compatible   true
        2つの色の間を線形補間した色を作成します。
        パラメーター t は[0, 1]の範囲に制限されます。
     */
    static Color    Lerp(const Color& a, const Color& b, float t);

    /*!
        @method     LerpUnclamped
        @unity-compatible   true
        2つの色の間を線形補間した色を作成します。
        パラメーター t の範囲は制限されません。
     */
    static Color    LerpUnclamped(const Color& a, const Color& b, float t);

    /*!
        @method     RGBToHSV
        @unity-compatible   true
        RGB 色空間の値から HSV 色空間の値を取得します。
     */
    static void     RGBToHSV(const Color& rgbColor, float& outH, float& outS, float& outV);
    
    static Color    SmoothStep(const Color& a, const Color& b, float t);


public:
#pragma mark - メンバ変数
    /*!
        @var    r
        @unity-compatible   true
        @abstract   赤の色成分（0.0〜1.0）
     */
    float   r;

    /*!
        @var    g
        @unity-compatible   true
        @abstract   緑の色成分（0.0〜1.0）
     */
    float   g;

    /*!
        @var    b
        @unity-compatible   true
        @abstract   青の色成分（0.0〜1.0）
     */
    float   b;

    /*!
        @var    a
        @unity-compatible   true
        @abstract   アルファの色成分（0.0〜1.0）
     */
    float   a;

public:
#pragma mark - コンストラクタ
    /*!
        @task   コンストラクタ
     */

    /*!
        @method     Color
        @unity-compatible   false
        赤、緑、青の各色成分が 0.0 で、アルファ成分が 1.0 の色を作成します。
     */
    Color();

    /*!
        @method     Color
        @unity-compatible   true
        赤、緑、青の各色成分を 0.0〜1.0 で指定して色を作成します。
     */
    Color(float r, float g, float b);

    /*!
        @method     Color
        @unity-compatible   true
        赤、緑、青、アルファ値の各色成分を 0.0〜1.0 で指定して色を作成します。
     */
    Color(float r, float g, float b, float a);

    /*!
         @method     Color
         @abstract   HTMLで指定するのと同じ色の値を 0xff99cc のような16進数の整数値で指定します。
     */
    Color(const unsigned color);

    /*!
        @method     Color
        @abstract   HTMLで指定するのと同じ "ff99cc" のような文字列で色を指定します。
     */
    Color(const std::string& str);
    
    /*!
        @method     Color
        @abstract   渡された色と同じ色情報をもつ色を作成します。
     */
    Color(const Color& color);

    /*!
        @method     Color
        @abstract   渡されたベクトルを利用して、r=x, g=y, b=z となるように、アルファ成分が 1.0 の色を作成します。
     */
    Color(const Vector3& vec);

    /*!
        @method     Color
        @abstract   渡されたベクトルを利用して、r=x, g=y, b=z, a=w となるように色を作成します。
     */
    Color(const Vector4& vec);

    
public:
#pragma mark - Public 関数
    Color   Alpha(float alpha) const;
    Color   Blue(float blue) const;
    Color   Green(float green) const;
    Color   Red(float red) const;

    /*!
        @method     ToString
        ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString() const override;

    /*!
        @method     ToString
        各要素に対して適用される書式を指定して、色の各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString(const std::string& format) const;

    /*!
        @method     c_str
        色の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str() const override;

    /*!
        @method     c_str
        各要素に対して適用される書式を指定して、色の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str(const std::string& format) const;

public:
#pragma mark - 演算子のオーバーロード
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method operator=
        @abstract 渡された色情報をこのオブジェクトにコピーします。
     */
    Color&  operator=(const Color& color);

    /*!
        @method operator==
        @abstract 渡された色の色情報とこのオブジェクトのもつ色情報が等しいかどうかをチェックします。
     */
    bool    operator==(const Color& color) const;

    /*!
        @method operator!=
        @abstract 渡された色の色情報とこのオブジェクトのもつ色情報が等しくないかどうかをチェックします。
     */
    bool    operator!=(const Color& color) const;

    /*!
        @method     operator+=
     */
    Color&  operator+=(const Color& color);

    /*!
        @method     operator-=
     */
    Color&  operator-=(const Color& color);

    /*!
        @method operator+
     */
    Color   operator+(const Color& color) const;

    /*!
        @method operator-
     */
    Color   operator-(const Color& color) const;

    /*!
        @method operator*
     */
    Color   operator*(const Color& color) const;

    /*!
        @method operator*
     */
    Color   operator*(float value) const;
    
    /*!
        @method operator/
     */
    Color   operator/(float value) const;

    /*!
        @method     (Vector3)
        3次元ベクトルに変換します。
     */
    operator   Vector3() const;

    /*!
        @method     (Vector4)
        @unity-compatible   true
        4次元ベクトルに変換します。
     */
    operator   Vector4() const;
    
};


#endif  //#ifndef __COLOR_HPP__


