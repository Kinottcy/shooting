//
//  DrawBatch.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "DrawBatch.hpp"
#include "GL_class.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <OpenGL/OpenGL.h>
#include <cmath>
#include "Settings.hpp"



bool    gGMIsDrawing    = false;



static __GMVertexDataVCNT   sGMBatchDrawVertexes[DRAW_BATCH_SIZE * 6];
static GMPrimitiveType      sGMBatchPrimitiveType = __GMPrimitiveTypeNone;
static int                  sGMBatchPrimitiveCount = 0;


void DrawBatch::Begin() throw(GameInvalidOperationError)
{
    if (gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::Begin() should not be invoked before DrawBatch::End() is called.");
    }
    gGMIsDrawing = true;
}

void DrawBatch::End() throw(GameInvalidOperationError)
{
    if (!gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::End() should not be invoked after DrawBatch::Begin().");
    }

    __FlushBatchDraws();
    
    gGMIsDrawing = false;
}

void DrawBatch::__FlushBatchDraws()
{
    // バッチ処理の存在をチェックしておく
    if (sGMBatchPrimitiveCount == 0) {
        return;
    }
    
    // ポイントスプライト使用の確認
    bool doPointSprite = false;
    if (sGMBatchPrimitiveType == GMPrimitiveTypePointList) {
        if (GL::IsPointSpriteEnabled() & GL::IsTextureEnabled()) {
            doPointSprite = true;
        }
    }
    
    // ポイントスプライトの有効化
    if (doPointSprite) {
        glEnable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    }

    // 頂点配列による描画の実行
    GL::__DrawPrimitivesUser(sGMBatchPrimitiveType, sGMBatchDrawVertexes, 0, sGMBatchPrimitiveCount);
    
    // ポイントスプライトの無効化
    if (doPointSprite) {
        glDisable(GL_POINT_SPRITE);
    }

    // バッチ処理の終了
    sGMBatchPrimitiveType = __GMPrimitiveTypeNone;
    sGMBatchPrimitiveCount = 0;
}

void DrawBatch::DrawPoint(const Vector2& pos, const Color& color, float size) throw(GameInvalidOperationError)
{
    DrawPoint(Vector3(pos, 0.0f), color, size);
}

void DrawBatch::DrawPoint(const Vector3& pos, const Color& color, float size) throw(GameInvalidOperationError)
{
    if (!gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::begin() should be invoked before calling drawing methods.");
    }
    
    // 色と点の大きさの決定
    Color theColor = color;
    if (GL::IsWireframeModeEnabled()) {
        size = 1.0f;
        theColor = Color::white;
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypePointList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypePointList;
        gGMPointSize = size;
    } else if (fabsf(gGMPointSize - size) > __FLT_EPSILON__) {
        __FlushBatchDraws();
        gGMPointSize = size;
    }
    
    // 頂点配列データの格納
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)pos.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)pos.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)pos.z;

    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = theColor.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = theColor.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = theColor.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = theColor.a;
    
    // 次のバッチ処理へ
    sGMBatchPrimitiveCount++;
}

void DrawBatch::DrawLine(const Vector2& p1, const Vector2& p2, const Color& color, float width) throw(GameInvalidOperationError)
{
    DrawLine(Vector3(p1, 0), Vector3(p2, 0), color, color, width);
}

void DrawBatch::DrawLine(const Vector2& p1, const Vector2& p2, const Color& c1, const Color& c2, float width) throw(GameInvalidOperationError)
{
    DrawLine(Vector3(p1, 0), Vector3(p2, 0), c1, c2, width);
}

void DrawBatch::DrawLine(const Vector3& p1, const Vector3& p2, const Color& color, float width) throw(GameInvalidOperationError)
{
    DrawLine(p1, p2, color, color, width);
}

void DrawBatch::FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3,
                          const Color& color,
                          const Vector2& t1, const Vector2& t2, const Vector2& t3) throw(GameInvalidOperationError)
{
    __FillTriangle(Vector3(p1, 0), Vector3(p2, 0), Vector3(p3, 0),
                   Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1),
                   color, color, color,
                   t1, t2, t3);
}

void DrawBatch::FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3,
                             const Color& c1, const Color& c2, const Color& c3,
                             const Vector2& t1, const Vector2& t2, const Vector2& t3) throw(GameInvalidOperationError)
{
    __FillTriangle(Vector3(p1, 0), Vector3(p2, 0), Vector3(p3, 0),
                   Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1),
                   c1, c2, c3,
                   t1, t2, t3);
}

void DrawBatch::FillTriangle(const Vector3& p1, const Vector3& p2, const Vector3& p3,
                             const Vector3& n1, const Vector3& n2, const Vector3& n3,
                             const Vector2& t1, const Vector2& t2, const Vector2& t3) throw(GameInvalidOperationError)
{
    Color color = Color::white;
    __FillTriangle(p1, p2, p3, n1, n2, n3, color, color, color, t1, t2, t3);
}

void DrawBatch::FillQuad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4,
                         const Color& color,
                         const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& t4) throw(GameInvalidOperationError)
{
    __FillQuad(Vector3(p1, 0), Vector3(p2, 0), Vector3(p3, 0), Vector3(p4, 0),
               Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1),
               color, color, color, color,
               t1, t2, t3, t4);
}

void DrawBatch::FillQuad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4,
                         const Color& c1, const Color& c2, const Color& c3, const Color& c4,
                         const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& t4) throw(GameInvalidOperationError)
{
    __FillQuad(Vector3(p1, 0), Vector3(p2, 0), Vector3(p3, 0), Vector3(p4, 0),
               Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1),
               c1, c2, c3, c4,
               t1, t2, t3, t4);
}

void DrawBatch::FillQuad(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4,
                         const Vector3& n1, const Vector3& n2, const Vector3& n3, const Vector3& n4,
                         const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& t4) throw(GameInvalidOperationError)
{
    Color color = Color::white;
    __FillQuad(p1, p2, p3, p4,
               n1, n2, n3, n4,
               color, color, color, color,
               t1, t2, t3, t4);
}

void DrawBatch::DrawLine(const Vector3& p1, const Vector3& p2, const Color& c1, const Color& c2, float width) throw(GameInvalidOperationError)
{
    if (!gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::Begin() should be invoked before calling drawing methods.");
    }
    
    // 色と線幅の決定
    Color theC1 = c1;
    Color theC2 = c2;
    if (GL::IsWireframeModeEnabled()) {
        width = 1.0f;
        theC1 = Color::white;
        theC2 = Color::white;
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeLineList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeLineList;
        gGMLineWidth = width;
    } else if (fabsf(gGMLineWidth - width) > __FLT_EPSILON__) {
        __FlushBatchDraws();
        gGMLineWidth = width;
    }

    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchPrimitiveCount++;
}

void DrawBatch::__FillTriangle(const Vector3& p1, const Vector3& p2, const Vector3& p3,
                               const Vector3& n1, const Vector3& n2, const Vector3& n3,
                               const Color& c1, const Color& c2, const Color& c3,
                               const Vector2& t1, const Vector2& t2, const Vector2& t3) throw(GameInvalidOperationError)
{
    if (!gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::Begin() should be invoked before calling drawing methods.");
    }
    
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeTriangleList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeTriangleList;
    }

    // 色の決定
    Color theC1 = c1;
    Color theC2 = c2;
    Color theC3 = c3;
    if (GL::IsWireframeModeEnabled()) {
        theC1 = Color::white;
        theC2 = Color::white;
        theC3 = Color::white;
    }
    
    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t1.y);
    sGMBatchPrimitiveCount++;
    
    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t2.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 3
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC3.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC3.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC3.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC3.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t3.y);
    sGMBatchPrimitiveCount++;
}

void DrawBatch::__FillQuad(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4,
                           const Vector3& n1, const Vector3& n2, const Vector3& n3, const Vector3& n4,
                           const Color& c1, const Color& c2, const Color& c3, const Color& c4,
                           const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& t4) throw(GameInvalidOperationError)
{
    if (!gGMIsDrawing) {
        throw GameInvalidOperationError("DrawBatch::Begin() should be invoked before calling drawing methods.");
    }
    
    // 異なる設定のプリミティブを描画する場合には、前のプリミティブ描画を掃き出しておく
    if (sGMBatchPrimitiveType != GMPrimitiveTypeTriangleList) {
        __FlushBatchDraws();
        sGMBatchPrimitiveType = GMPrimitiveTypeTriangleList;
    }

    // 色の決定
    Color theC1 = c1;
    Color theC2 = c2;
    Color theC3 = c3;
    Color theC4 = c4;
    if (GL::IsWireframeModeEnabled()) {
        theC1 = Color::white;
        theC2 = Color::white;
        theC3 = Color::white;
        theC4 = Color::white;
    }
    
    // 頂点配列データの格納 1
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC1.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC1.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC1.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC1.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n1.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n1.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t1.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t1.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 2
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC2.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC2.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC2.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC2.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n2.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n2.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t2.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t2.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 3
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p4.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p4.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC4.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC4.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC4.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC4.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n4.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n4.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t4.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t4.y);
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 4
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount] = sGMBatchDrawVertexes[sGMBatchPrimitiveCount-1];
    sGMBatchPrimitiveCount++;
    
    // 頂点配列データの格納 5
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount] = sGMBatchDrawVertexes[sGMBatchPrimitiveCount-3];
    sGMBatchPrimitiveCount++;

    // 頂点配列データの格納 6
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vx = (GLfloat)p3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vy = (GLfloat)p3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].vz = (GLfloat)p3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cr = (GLfloat)theC3.r;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cg = (GLfloat)theC3.g;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].cb = (GLfloat)theC3.b;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ca = (GLfloat)theC3.a;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nx = (GLfloat)n3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ny = (GLfloat)n3.y;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].nz = (GLfloat)n3.z;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].tx = (GLfloat)t3.x;
    sGMBatchDrawVertexes[sGMBatchPrimitiveCount].ty = (GLfloat)(1.0f - t3.y);
    sGMBatchPrimitiveCount++;
}

