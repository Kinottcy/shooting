//
//  Camera.cpp
//  Game Framework
//
//  Created by numata on July 3, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "Camera.hpp"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>


Camera::Camera()
{
    mProjectionMatrix = Matrix4x4::identity;
    mViewMatrix = Matrix4x4::identity;
    mWorldMatrix = Matrix4x4::identity;
}

void Camera::Clear(const Color& color) const
{
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Matrix4x4 Camera::GetProjectionMatrix() const
{
    return mProjectionMatrix;
}

Matrix4x4 Camera::GetViewMatrix() const
{
    return mViewMatrix;
}

Matrix4x4 Camera::GetWorldMatrix() const
{
    return mWorldMatrix;
}

void Camera::SetProjectionMatrix(const Matrix4x4& matrix)
{
    mProjectionMatrix = matrix;

}

void Camera::SetViewMatrix(const Matrix4x4& matrix)
{
    mViewMatrix = matrix;
}

void Camera::SetWorldMatrix(const Matrix4x4& matrix)
{
    mWorldMatrix = matrix;

}

void Camera::Set()
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(mProjectionMatrix.mat);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((mWorldMatrix * mViewMatrix).mat);
}


