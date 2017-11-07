//
//  Quaternion.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__


#include "GMObject.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

struct Matrix4x4;


/*
    http://blogs.msdn.com/b/ito/archive/2009/05/01/more-bones-04.aspx より
    クォータニオンを使うと便利
        ・アニメーションデータが多すぎるので圧縮したい（キーフレーム間の回転補間）
        ・自由に回転状態を変化させたい（岩などのオブジェクトが地面の起伏の状態によって回転状態が変化する場合、飛行機などの姿勢制御）
        ・回転状態を変化させる必要はないけど対象となるオブジェクトが大量にある（爆発などで大量の破片がランダムに回転しながら飛び散るエフェクト）
    オイラー角で十分
        ・制限された回転（FPS、TPSなどのカメラコントロール）
        ・回転状態を変化する必要がない（爆発などで少数の破片がランダムに回転しながら飛び散るエフェクト）
        ・誤差があっても大丈夫（回転の結合が短時間だけ必要な場合、上記のエフェクトなどカットシーン的な場面で使われる回転） 
 */

/*!
    @class      Quaternion
    @group      Math
    @unity-compatible   true
    クォータニオンを表現するクラスです。
 */
struct Quaternion : public GMObject
{    
public:
#pragma mark - Static 変数
    /*!
        @task   Static 変数
     */
    /*!
        @const  identity
        @unity-compatible   true
        単位回転を表すクォータニオンです。
     */
    static const Quaternion&    identity;


public:
#pragma mark - Static 関数
    /*!
        @task   Static 関数
     */

    /*!
        @method     Angle
        @unity-compatible   true
        2つの回転 a と b の間の角度をラジアン単位で返します。
     */
    static float        Angle(const Quaternion& a, const Quaternion& b);

    /*!
        @method     AngleAxis
        @unity-compatible   true
        axis の周りを degree 度回転する回転を作成します。
     */
    static Quaternion   AngleAxis(float degree, const Vector3& axis);

    /*!
        @method     Dot
        @unity-compatible   true
        2つの回転の内積を返します。
     */
    static float        Dot(const Quaternion& a, const Quaternion& b);
    
    /*!
        @method     Euler
        @unity-compatible   true
     */
    static Quaternion   Euler(float xDegree, float yDegree, float zDegree);

    /*!
        @method     Euler
        @unity-compatible   true
     */
    static Quaternion   Euler(const Vector3& euler);

    /*!
        @method     EaseIn
        @unity-compatible   false
     */
    static Quaternion   EaseIn(const Quaternion& a, const Quaternion& b, float t);
    
    /*!
        @method     EaseInOut
        @unity-compatible   false
     */
    static Quaternion   EaseInOut(const Quaternion& a, const Quaternion& b, float t);
    
    /*!
        @method     EaseOut
        @unity-compatible   false
     */
    static Quaternion   EaseOut(const Quaternion& a, const Quaternion& b, float t);

    /*!
        @method     FromToRotation
        @unity-compatible   true
     */
    static Quaternion   FromToRotation(const Vector3& fromDir, const Vector3& toDir);

    /*!
        @method     Inverse
        @unity-compatible   true
        クォータニオンの正反対の値となる値を返します。
     */
    static Quaternion   Inverse(const Quaternion& rotation);

    /*!
        @method     Lerp
        @unity-compatible   true
     */
    static Quaternion   Lerp(const Quaternion& a, const Quaternion& b, float t);

    /*!
        @method     LerpUnclamped
        @unity-compatible   true
     */
    static Quaternion   LerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

    /*!
        @method     LookRotation
        @unity-compatible   true (unsupported)
     */
    static Quaternion   LookRotation(const Vector3& forward, const Vector3& upwards = Vector3::up);

    /*!
        @method     RotateTowards
        @unity-compatible   true
     */
    static Quaternion   RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);

    /*!
        @method     Slerp
        @unity-compatible   true
     */
    static Quaternion   Slerp(const Quaternion& a, const Quaternion& b, float t);

    /*!
        @method     SlerpUnclamped
        @unity-compatible   true
     */
    static Quaternion   SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

    static Quaternion   SmoothStep(const Quaternion& a, const Quaternion& b, float t);

    
public:
    /*!
        @var    x
     */
    float x;

    /*!
        @var    y
     */
    float y;

    /*!
        @var    z
     */
    float z;

    /*!
        @var    w
     */
    float w;
    

public:
#pragma mark - コンストラクタ
    /*!
        @task   コンストラクタ
     */
    
    /*!
        @method     Quaternion
     */
    Quaternion();
    
    /*!
        @method     Quaternion
     */
    Quaternion(float x, float y, float z, float w);
    
    /*!
        @method     Quaternion
     */
    Quaternion(const Quaternion& quat);
    
    Quaternion(const Vector4& vec);

    /*!
        @method     Quaternion
     */
    Quaternion(const Matrix4x4& mat);


public:
#pragma mark - Public 関数
    /*!
        @task   Public 関数
     */
    
    /*!
        @method     Concat
        @unity-compatible   false
     */
    Quaternion      Concat(const Quaternion& quat) const;

    /*!
        @method     Conjugate
        @unity-compatible   false
     */
    Quaternion&     Conjugate();

    /*!
        @method     Magnitude
        @unity-compatible   false
     */
    float           Magnitude() const;
    
    /*!
        @method     Normalized
        @unity-compatible   false
     */
    Quaternion      Normalized() const;
    
    /*!
        @method     Normalize
        @unity-compatible   false
     */
    void            Normalize();

    /*!
        @method     Set
        @unity-compatible   true
        既存の Quaternion に x、y、z、w の成分を設定します。
     */
    void            Set(float x, float y, float z, float w);

    /*!
        @method     SqrMagnitude
        @unity-compatible   false
     */
    float           SqrMagnitude() const;
    
    /*!
        @method     ToMatrix4x4
        @unity-compatible   false
     */
    Matrix4x4       ToMatrix4x4() const;

    /*!
        @method     ToString
        @unity-compatible   true
        ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string     ToString() const override;

    /*!
        @method     ToString
        @unity-compatible   true
        各要素に対して適用される書式を指定して、クォータニオンの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string     ToString(const std::string& format) const;

    /*!
        @method     c_str
        クォータニオンの各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str() const override;

    /*!
        @method     c_str
        @unity-compatible   false
        各要素に対して適用される書式を指定して、クォータニオンの各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char*     c_str(const std::string& format) const;

public:
#pragma mark - 演算子のオーバーロード
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    Quaternion&     operator=(const Quaternion& quat);    
    
    /*!
        @method     operator-
     */
    Quaternion      operator-() const;
    
    /*!
        @method     operator+
     */
    Quaternion      operator+(const Quaternion& quat) const;
    
    /*!
        @method     operator-
     */
    Quaternion      operator-(const Quaternion& quat) const;
    
    /*!
        @method     operator*
     */
    Quaternion      operator*(const Quaternion& quat) const;
    
    /*!
        @method     operator*
     */
    Quaternion      operator*(float scale) const;

    /*!
        @method     operator*
     */
    Vector2         operator*(const Vector2& vec) const;

    /*!
        @method     operator*
     */
    Vector3         operator*(const Vector3& vec) const;

    /*!
        @method     operator*
     */
    Vector4         operator*(const Vector4& vec) const;

    /*!
        @method     operator/
     */
    Quaternion      operator/(const Quaternion& quat) const;
    
    /*!
        @method     operator/
     */
    Quaternion      operator/(float value) const;

    
    /*!
        @method     operator+=
     */
    Quaternion&     operator+=(const Quaternion& quat);
    
    /*!
        @method     operator-=
     */
    Quaternion&     operator-=(const Quaternion& quat);
    
    /*!
        @method     operator*=
     */
    Quaternion&     operator*=(const Quaternion& quat);
    
    /*!
        @method     operator=
     */
    Quaternion&     operator*=(float scale);
    
    /*!
        @method     operator/=
     */
    Quaternion&     operator/=(const Quaternion& quat);
    
    /*!
        @method     operator/=
     */
    Quaternion&     operator/=(float value);

    
    /*!
        @method     operator==
     */
    bool        operator==(const Quaternion& quat) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const Quaternion& quat) const;

    operator   Vector4() const;

};


#endif  //#ifndef __QUATERNION_HPP__


