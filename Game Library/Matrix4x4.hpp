//
//  Matrix4x4.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __MATRIX4X4_HPP__
#define __MATRIX4X4_HPP__


#include "GMObject.hpp"
#include "GameError.hpp"

struct Matrix4x4;
struct GMPlane;
struct Quaternion;
struct Vector2;
struct Vector3;
struct Vector4;


/*
    ///// 2D設定
    g->setProjectionMatrix(Matrix4x4::CreateOrthographicOffCenter(0.0f, Screen::width, 0.0f, Screen::height, 1.0f, 1500.0f));
    g->setViewMatrix(Matrix4x4::identity);
 
    ///// 3D設定
    // 視錐体の設定
    //   35mmフィルムに対する実際のレンズの画角例
    //     ・望遠域（135mmレンズで18度、300mmレンズで8度）
    //     ・標準域（肉眼に近い）（50mmレンズで45度）
    //     ・広角域（35mmレンズで62度、24mmレンズで84度、20mmレンズで94度）
    Vector2 screenSize = g->getScreenSize();
    g->setProjectionMatrix(Matrix4x4::CreatePerspectiveFieldOfView(M_PI/4, (float)Screen::width/Screen::height, 1.0f, 1500.0f));
 */


/*!
    @class      Matrix4x4
    @group      Math
    @abstract   4x4 の変換行列をサポートするためのクラスです。
 */
struct Matrix4x4 : public GMObject
{
public:
    /*!
        @const  identity
     */
    static const Matrix4x4&  identity;

    /*!
        @const  zero
     */
    static const Matrix4x4&  zero;

public:
    union {
        float   mat[16];
        struct {
            /*!
                @var m00
             */
            float m00;

            /*!
                @var m01
             */
            float m01;

            /*!
                @var m02
             */
            float m02;

            /*!
                @var m03
             */
            float m03;
            
            /*!
                @var m10
             */
            float m10;
            
            /*!
                @var m11
             */
            float m11;
            
            /*!
                @var m12
            */
            float m12;
            
            /*!
                @var m13
             */
            float m13;

            /*!
                @var m20
             */
            float m20;
            
            /*!
                @var m21
             */
            float m21;

            /*!
                @var m22
             */
            float m22;
            
            /*!
                @var m23
             */
            float m23;
            
            /*!
                @var m30
             */
            float m30;

            /*!
                @var m31
             */
            float m31;

            /*!
                @var m32
             */
            float m32;

            /*!
                @var m33
             */
            float m33;
        };
    };
    
    /*!
        @task   Static関数
     */
    
    /*!
        @method     Billboard
     */
    static Matrix4x4    Billboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUpVec);
    
    /*!
        @method     ConstrainedBillboard
     */
    static Matrix4x4    ConstrainedBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& rotateAxis,
                                             const Vector3& cameraForwardVec, const Vector3& objectForwardVec);
    
    /*!
        @method     LookAt
     */
    static Matrix4x4    LookAt(const Vector3& from, const Vector3& to, const Vector3& up);
    
    /*!
        @method     Ortho
     */
    static Matrix4x4    Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
    /*!
        @method     Perspective
     */
    static Matrix4x4    Perspective(float fov, float aspect, float zNear, float zFar);

    /*!
        @method     RotationX
     */
    static Matrix4x4    RotationX(float rad);
    
    /*!
        @method     RotationY
     */
    static Matrix4x4    RotationY(float rad);
    
    /*!
        @method     RotationZ
     */
    static Matrix4x4    RotationZ(float rad);

    /*!
        @method     Scale
     */
    static Matrix4x4    Scale(float x, float y);

    /*!
        @method     Scale
     */
    static Matrix4x4    Scale(const Vector2& vec);

    /*!
        @method     Scale
     */
    static Matrix4x4    Scale(float x, float y, float z);
    
    /*!
        @method     Scale
        @unity-compatible   true
     */
    static Matrix4x4    Scale(const Vector3& vec);

    /*!
        @method     Translation
     */
    static Matrix4x4    Translation(float x, float y);

    /*!
        @method     Translation
     */
    static Matrix4x4    Translation(const Vector2& pos);

    /*!
        @method     Translation
     */
    static Matrix4x4    Translation(float x, float y, float z);

    /*!
        @method     Translation
     */
    static Matrix4x4    Translation(const Vector3& pos);

    /*!
        @method     TRS
        @unity-compatible   true
     */
    static Matrix4x4    TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);


#pragma mark - 数値補完
    /*!
        @task   数値補完
     */
    
    /*!
        @method     EaseIn
     */
    static Matrix4x4     EaseIn(const Matrix4x4& mat1, const Matrix4x4& mat2, float amount);

    /*!
        @method     EaseInOut
     */
    static Matrix4x4     EaseInOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float amount);

    /*!
        @method     EaseOut
     */
    static Matrix4x4     EaseOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float amount);
    
    /*!
        @method     Lerp
     */
    static Matrix4x4     Lerp(const Matrix4x4& mat1, const Matrix4x4& mat2, float amount);
    
    static Matrix4x4     SmoothStep(const Matrix4x4& mat1, const Matrix4x4& mat2, float amount);


public:
#pragma mark - コンストラクタ
    /*!
        @task コンストラクタ
     */

    /*!
        @method     Matrix4x4
        @abstract   すべての要素が 0.0 の行列を生成します。
     */
    Matrix4x4();

    /*!
        @method     Matrix4x4
        @abstract   各要素を設定して行列を生成します。
     */
    Matrix4x4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33);

    /*!
        @method     Matrix4x4
        @abstract   各要素をコピーして行列を生成します。
     */
    Matrix4x4(const Quaternion& quat);


public:
#pragma mark - Public 関数
    /*!
        @task   Public 関数
     */
    
    /*!
        @method     Decompose
     */
    bool        Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;

    /*!
        @method     Determinant
        @unity-compatible   true
        この行列の行列式を計算します。
     */
    float       Determinant() const;
    
    /*!
        @method     Inverse
     */
    Matrix4x4   Inverse() const throw(GameArithmeticError);

    /*!
        @method     ToQuaternion
     */
    Quaternion  ToQuaternion() const;
    
    /*!
        @method     Transpose
        @abstract   この行列の転置行列を求めます。
     */
    Matrix4x4   Transpose() const;
    
    /*!
        @method setBackward
     */
    void    setBackward(const Vector3& vec);
    
    /*!
        @method setDown
     */
    void    setDown(const Vector3& vec);
    
    /*!
        @method setForward
     */
    void    setForward(const Vector3& vec);
    
    /*!
        @method setLeft
     */
    void    setLeft(const Vector3& vec);
    
    /*!
        @method setRight
     */
    void    setRight(const Vector3& vec);
    
    /*!
        @method setTranslation
     */
    void    setTranslation(const Vector3& vec);
    
    /*!
        @method setUp
     */
    void    setUp(const Vector3& vec);

    /*!
        @method     ToString
        行列の各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString() const override;

    /*!
        @method     ToString
        各要素に対して適用される書式を指定して、行列の各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString(const std::string& format) const;

    /*!
        @method     c_str
        行列の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str() const override;
    /*!
        @method     c_str
        各要素に対して適用される書式を指定して、行列の各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str(const std::string& format) const;

public:
#pragma mark - 演算子のオーバーロード
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        @method     operator=
     */
    Matrix4x4&  operator=(const Matrix4x4& matrix);
    
    /*!
        @method     operator-
     */
    Matrix4x4   operator-() const;

    /*!
        @method     operator+
     */
    Matrix4x4   operator+(const Matrix4x4& matrix) const;

    /*!
        @method     operator-
     */
    Matrix4x4   operator-(const Matrix4x4& matrix) const;

    /*!
        @method     operator*
     */
    Matrix4x4   operator*(const Matrix4x4& matrix) const;

    /*!
        @method     operator/
     */
    Matrix4x4   operator/(const Matrix4x4& matrix) const;

    /*!
        @method     operator*
     */
    Matrix4x4   operator*(float value) const;

    /*!
        @method     operator*
     */
    Vector2     operator*(const Vector2& vector) const;

    /*!
        @method     operator*
     */
    Vector3     operator*(const Vector3& vector) const;

    /*!
        @method     operator*
     */
    Vector4     operator*(const Vector4& vector) const;

    /*!
        @method     operator/
     */
    Matrix4x4   operator/(float value) const;
    
    
    friend Matrix4x4 operator*(float value, const Matrix4x4& matrix);
    
    
    /*!
        @method     operator+=
     */
    Matrix4x4&   operator+=(const Matrix4x4& matrix);
    
    /*!
        @method     operator-=
     */
    Matrix4x4&   operator-=(const Matrix4x4& matrix);
    
    /*!
        @method     operator*=
     */
    Matrix4x4&   operator*=(const Matrix4x4& matrix);
    
    /*!
        @method     operator/=
     */
    Matrix4x4&   operator/=(const Matrix4x4& matrix);
    
    /*!
        @method     operator*=
     */
    Matrix4x4&   operator*=(float value);
    
    /*!
        @method     operator/=
     */
    Matrix4x4&   operator/=(float value);
    
    
    /*!
        @method     operator==
     */
    bool        operator==(const Matrix4x4& matrix) const;
    
    /*!
        @method     operator!=
     */
    bool        operator!=(const Matrix4x4& matrix) const;
    
};


#endif  //#ifndef __MATRIX4X4_HPP__


