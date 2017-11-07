//
//  GL_class.cpp
//  Game Framework
//
//  Created by numata on Sep 06, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#include "GL_class.hpp"
#include <OpenGL/glu.h>


BlendMode   GL::sBlendMode              = BlendModeAlpha;
bool        GL::sIsDepthTestEnabled     = false;
bool        GL::sIsLightingEnabled      = false;
bool        GL::sIsPointSpriteEnabled   = false;
bool        GL::sIsScissorTestEnabled   = false;
bool        GL::sIsTextureEnabled       = false;
Texture*    GL::sTexture                = NULL;
bool        GL::sUsesWireframe          = false;
Rect        GL::sViewportRect;


float   gGMLineWidth    = 1.0f;
float   gGMPointSize    = 1.0f;


std::string GetBlendModeName(BlendMode mode)
{
    switch (mode) {
        case BlendModeNone:
            return "None";
        case BlendModeAlpha:
            return "Alpha";
        case BlendModeAdd:
            return "Add";
        case BlendModeClear:
            return "Clear";
        case BlendModeCopy:
            return "Copy";
        case BlendModeInvert:
            return "Invert";
        case BlendModeMultiply:
            return "Multiply";
        case BlendModeScreen:
            return "Screen";
        case BlendModeXOR:
            return "XOR";
    }
}


#pragma mark - Static 関数

void GL::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVC* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVC), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(GMVertexDataVC), p);
    //p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0f;
    gGMLineWidth = 0.0f;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void GL::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0f;
    gGMLineWidth = 0.0f;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GL::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVCT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVCT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0f;
    gGMLineWidth = 0.0f;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GL::DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVNT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(GMVertexDataVNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点の法線ベクトル
    glNormalPointer(GL_FLOAT, sizeof(GMVertexDataVNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(GMVertexDataVNT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0f;
    gGMLineWidth = 0.0f;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void GL::__DrawPrimitivesUser(GMPrimitiveType type, __GMVertexDataVCNT* data, int startIndex, int primitiveCount)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    // 頂点の座標
    unsigned char* p = (unsigned char*)data;
    glVertexPointer(3, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のカラー
    glColorPointer(4, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 4);
    
    // 頂点の法線ベクトル
    glNormalPointer(GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    p = (unsigned char*)(((GLfloat*)p) + 3);
    
    // 頂点のテクスチャ座標
    glTexCoordPointer(2, GL_FLOAT, sizeof(__GMVertexDataVCNT), p);
    
    // 描画の実行
    if (type == GMPrimitiveTypePointList) {
        glPointSize((GLfloat)gGMPointSize);
        glDrawArrays(GL_POINTS, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineList) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeLineStrip) {
        glLineWidth((GLfloat)gGMLineWidth);
        glDrawArrays(GL_LINE_STRIP, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleList) {
        glDrawArrays(GL_TRIANGLES, 0, primitiveCount);
    } else if (type == GMPrimitiveTypeTriangleStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, primitiveCount);
    }
    
    gGMPointSize = 0.0f;
    gGMLineWidth = 0.0f;
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void GL::EnableDepthTest(bool flag)
{
    if (!(sIsDepthTestEnabled ^ flag)) {
        return;
    }
    sIsDepthTestEnabled = flag;
    
    if (sIsDepthTestEnabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void GL::EnableLight(int index, bool flag)
{
    if (flag) {
        if (index == 0) {
            glEnable(GL_LIGHT0);
        } else if (index == 1) {
            glEnable(GL_LIGHT1);
        } else if (index == 2) {
            glEnable(GL_LIGHT2);
        } else if (index == 3) {
            glEnable(GL_LIGHT3);
        } else if (index == 4) {
            glEnable(GL_LIGHT4);
        } else if (index == 5) {
            glEnable(GL_LIGHT5);
        } else if (index == 6) {
            glEnable(GL_LIGHT6);
        } else if (index == 7) {
            glEnable(GL_LIGHT7);
        } else {
            // TODO: エラー処理
        }
    } else {
        if (index == 0) {
            glDisable(GL_LIGHT0);
        } else if (index == 1) {
            glDisable(GL_LIGHT1);
        } else if (index == 2) {
            glDisable(GL_LIGHT2);
        } else if (index == 3) {
            glDisable(GL_LIGHT3);
        } else if (index == 4) {
            glDisable(GL_LIGHT4);
        } else if (index == 5) {
            glDisable(GL_LIGHT5);
        } else if (index == 6) {
            glDisable(GL_LIGHT6);
        } else if (index == 7) {
            glDisable(GL_LIGHT7);
        } else {
            // TODO: エラー処理
        }
    }
}

void GL::EnableLighting(bool flag)
{
    sIsLightingEnabled = flag;
    
    if (sIsLightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_NORMALIZE);
    }
}

void GL::EnablePointSprite(bool flag)
{
    sIsPointSpriteEnabled = flag;
}

void GL::EnableScissorTest(bool flag)
{
    if (!(sIsScissorTestEnabled ^ flag)) {
        return;
    }
    sIsScissorTestEnabled = flag;
    
    if (sIsScissorTestEnabled) {
        glEnable(GL_SCISSOR_TEST);
    } else {
        glDisable(GL_SCISSOR_TEST);
    }
}

void GL::EnableTexture(bool flag)
{
    sIsTextureEnabled = flag;
    if (sIsTextureEnabled) {
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}

void GL::EnableWireframeMode(bool flag)
{
    sUsesWireframe = flag;
    if (sUsesWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

BlendMode GL::GetBlendMode()
{
    return sBlendMode;
}

Texture* GL::GetTexture()
{
    return sTexture;
}

Rect GL::GetViewport()
{
    return sViewportRect;
}

bool GL::IsDepthTestEnabled()
{
    return sIsDepthTestEnabled;
}

bool GL::IsLightingEnabled()
{
    return sIsLightingEnabled;
}

bool GL::IsPointSpriteEnabled()
{
    return sIsPointSpriteEnabled;
}

bool GL::IsScissorTestEnabled()
{
    return sIsScissorTestEnabled;
}

bool GL::IsTextureEnabled()
{
    return sIsTextureEnabled;
}

bool GL::IsWireframeModeEnabled()
{
    return sUsesWireframe;
}

void GL::SetBlendMode(BlendMode mode)
{
    if (sBlendMode == mode) {
        return;
    }
    
    // アルファブレンディングの設定の反映
    sBlendMode = mode;
    switch (sBlendMode) {
        case BlendModeCopy:
            // コピー合成（単純な上書き）
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
            
        case BlendModeInvert:
            // 反転合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            break;
            
        case BlendModeXOR:
            // XOR合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
            break;
            
        case BlendModeMultiply:
            // 乗算合成
            glBlendFunc(GL_ZERO, GL_SRC_COLOR);
            break;
            
        case BlendModeScreen:
            // スクリーン合成
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
            break;
            
        case BlendModeAdd:
            // 加算合成（覆い焼き（リニア））
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
            
        case BlendModeClear:
            // クリア
            glBlendFunc(GL_ZERO, GL_ZERO);
            break;
            
        case BlendModeAlpha:
        default:
            // アルファ合成
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFunc(GL_ONE,  GL_ONE_MINUS_SRC_ALPHA);
            break;
    }
}

static void SetLightf(GLenum type, int index, GLfloat value)
{
    if (index == 0) {
        glLightf(GL_LIGHT0, type, value);
    } else if (index == 1) {
        glLightf(GL_LIGHT1, type, value);
    } else if (index == 2) {
        glLightf(GL_LIGHT2, type, value);
    } else if (index == 3) {
        glLightf(GL_LIGHT3, type, value);
    } else if (index == 4) {
        glLightf(GL_LIGHT4, type, value);
    } else if (index == 5) {
        glLightf(GL_LIGHT5, type, value);
    } else if (index == 6) {
        glLightf(GL_LIGHT6, type, value);
    } else if (index == 7) {
        glLightf(GL_LIGHT7, type, value);
    } else {
        // TODO: エラー処理
    }
}

static void SetLightfv(GLenum type, int index, const Vector4& vec)
{
    GLfloat params[] = { (GLfloat)vec.x, (GLfloat)vec.y, (GLfloat)vec.z, (GLfloat)vec.w };
    
    if (index == 0) {
        glLightfv(GL_LIGHT0, type, params);
    } else if (index == 1) {
        glLightfv(GL_LIGHT1, type, params);
    } else if (index == 2) {
        glLightfv(GL_LIGHT2, type, params);
    } else if (index == 3) {
        glLightfv(GL_LIGHT3, type, params);
    } else if (index == 4) {
        glLightfv(GL_LIGHT4, type, params);
    } else if (index == 5) {
        glLightfv(GL_LIGHT5, type, params);
    } else if (index == 6) {
        glLightfv(GL_LIGHT6, type, params);
    } else if (index == 7) {
        glLightfv(GL_LIGHT7, type, params);
    } else {
        // TODO: エラー処理
    }
}

static void SetLightfv(GLenum type, int index, const Vector3& vec)
{
    SetLightfv(type, index, Vector4(vec, 1.0f));
}

void GL::SetLightAmbientColor(int lightIndex, const Color& color)
{
    SetLightfv(GL_AMBIENT, lightIndex, (Vector3)color);
}

void GL::SetLightAttenuation(int lightIndex, float constant, float linear, float quadratic)
{
    SetLightf(GL_CONSTANT_ATTENUATION, lightIndex, (GLfloat)constant);
    SetLightf(GL_LINEAR_ATTENUATION, lightIndex, (GLfloat)linear);
    SetLightf(GL_QUADRATIC_ATTENUATION, lightIndex, (GLfloat)quadratic);
}

void GL::SetLightDiffuseColor(int lightIndex, const Color& color)
{
    SetLightfv(GL_DIFFUSE, lightIndex, (Vector3)color);
}

void GL::SetLightSpecularColor(int lightIndex, const Color& color)
{
    SetLightfv(GL_SPECULAR, lightIndex, (Vector3)color);
}

void GL::SetLightTypeAsPoint(int lightIndex, const Vector3& vecPosition)
{
    SetLightfv(GL_POSITION, lightIndex, Vector4(vecPosition, 1.0f));
}

void GL::SetLightTypeAsParallel(int lightIndex, const Vector3& vecDirection)
{
    SetLightfv(GL_POSITION, lightIndex, Vector4(vecDirection, 0.0f));
}

void GL::SetLightTypeAsSpot(int lightIndex, const Vector3& pos, const Vector3& dir, float radAngle, float exponent)
{
    SetLightfv(GL_POSITION, lightIndex, Vector4(pos, 1.0f));
    SetLightfv(GL_SPOT_DIRECTION, lightIndex, dir);
    SetLightf(GL_SPOT_CUTOFF, lightIndex, (GLfloat)(radAngle / 2 * Mathf::Rad2Deg));
    SetLightf(GL_SPOT_EXPONENT, lightIndex, (GLfloat)exponent);
}

void GL::SetTexture(Texture* tex)
{
    sTexture = tex;
    if (sTexture != NULL) {
        glBindTexture(GL_TEXTURE_2D, sTexture->GetName());
    } else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void GL::SetViewport(const Game::Rect& rect)
{
    sViewportRect = rect;
    glViewport(sViewportRect.x, sViewportRect.y, sViewportRect.width, sViewportRect.height);
    /*if (sIsScissorTestEnabled) {
        glScissor(sViewportRect.x, sViewportRect.y, sViewportRect.width, sViewportRect.height);
    }*/
}


