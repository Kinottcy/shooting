//
//  Rect.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __RECT_HPP__
#define __RECT_HPP__


#include "GMObject.hpp"

struct Vector2;
struct Vector3;


namespace Game
{

/*!
    @class  Rect
    @group  Math
    @unity-compatible   true
 */
struct Rect : public GMObject
{
public:
    /*!
        @task   Static 関数
     */

    /*!
        @method     MinMaxRect
        @unity-compatible   true
     */
    static Rect     MinMaxRect(float xmin, float ymin, float xmax, float ymax);

    /*!
        @method     NormalizedToPoint
        @unity-compatible   true
     */
    static Vector2  NormalizedToPoint(Rect rectangle, Vector2 normalizedRectCoordinates);

    /*!
        @method     PointToNormalized
        @unity-compatible   true
     */
    static Vector2  PointToNormalized(Rect rectangle, Vector2 point);

public:
    /*!
        @var    x
     */
    float  x;

    /*!
        @var    y
     */
    float  y;

    /*!
        @var    width
     */
    float  width;

    /*!
        @var    height
     */
    float  height;
    
public:
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     Rect
     */
    Rect();
    
    /*!
        @method     Rect
     */
    Rect(float x, float y, float width, float height);

    /*!
        @method     Rect
     */
    Rect(const Vector2& pos, const Vector2& size);

    /*!
        @method     Rect
     */
    Rect(const Rect& rect);

public:
    /*!
        @task   Public 関数
     */

    Vector2     Center() const;
    
    /*!
        @method     Contains
     */
    bool        Contains(const Vector2& pos) const;

    /*!
        @method     Contains
     */
    bool        Contains(const Vector3& pos) const;

    /*!
        @method     Contains
     */
    bool        Contains(const Rect& rect) const;
    
    /*!
        @method     Max
     */
    Vector2     Max() const;

    /*!
        @method     Min
     */
    Vector2     Min() const;

    /*!
        @method     Overlaps
     */
    bool        Overlaps(const Rect& rect) const;

    /*!
        @method     Position
     */
    Vector2     Position() const;

    /*!
        @method     Set
     */
    void        Set(float x, float y, float width, float height);

    /*!
        @method     Size
     */
    Vector2     Size() const;

    /*!
        @method     xMax
     */
    float       xMax() const;
    
    /*!
        @method     yMax
     */
    float       yMax() const;
    
    /*!
        @method     xMin
     */
    float       xMin() const;
    
    /*!
        @method     yMin
     */
    float       yMin() const;
    
    /*!
        @method     ToString
        ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString() const override;

    /*!
        @method     ToString
        各要素に対して適用される書式を指定して、矩形の各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString(const std::string& format) const;

    /*!
        @method     c_str
        矩形の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str() const override;

    /*!
        @method     c_str
        各要素に対して適用される書式を指定して、矩形の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str(const std::string& format) const;

public:
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    Rect&   operator=(const Rect& rect);
    
    /*!
        @method     operator==
     */
    bool        operator==(const Rect& rect) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const Rect& rect) const;
    
    /*!
        @method     operator+
     */
    Rect        operator+(const Vector2& vec) const;

    /*!
        @method     operator-
     */
    Rect        operator-(const Vector2& vec) const;

    /*!
        @method     operator+=
     */
    Rect&       operator+=(const Vector2& vec);
    
    /*!
        @method     operator-=
     */
    Rect&       operator-=(const Vector2& vec);

};  // struct Rect
    
};  // namespace Game

#endif  //#ifndef __RECT_HPP__

