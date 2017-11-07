//
//  Camera.hpp
//  Game Framework
//
//  Created by numata on July 3, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__


#include "Matrix4x4.hpp"
#include "Color.hpp"


class Camera : public GMObject
{
    Matrix4x4   mProjectionMatrix;
    Matrix4x4   mViewMatrix;
    Matrix4x4   mWorldMatrix;
    
public:
    /*!
        @task   コンストラクタ
     */
    Camera();    

public:
    /*!
        @task   Public 関数
     */
    void        Clear(const Color& color) const;

    Matrix4x4   GetProjectionMatrix() const;
    Matrix4x4   GetViewMatrix() const;
    Matrix4x4   GetWorldMatrix() const;
    
    void    SetProjectionMatrix(const Matrix4x4& matrix);
    void    SetViewMatrix(const Matrix4x4& matrix);
    void    SetWorldMatrix(const Matrix4x4& matrix);
    
    void    Set();
};


#endif  //#ifndef __CAMERA_HPP__


