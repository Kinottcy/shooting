//
//  DrawBatch.hpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __DRAW_BATCH_HPP__
#define __DRAW_BATCH_HPP__

#include "GMObject.hpp"
#include "Color.hpp"
#include "Types.hpp"
#include "Texture.hpp"
#include "GameError.hpp"


extern bool     gGMIsDrawing;


/*!
    @class      DrawBatch
    @group      Graphics
    @abstract   ポリゴンを作成して簡易な画面描画を行う機能を提供するためのクラスです。<br/>色とテクスチャを指定して、点、線、三角形、四角形を描画することができます。
    <p>このクラスにおける複数の描画処理は、可能な限りまとめられてバッチ処理されます。<br/><strong>描画の前後で必ず DrawBatch::Begin() メソッドと DrawBatch::End() メソッドを呼び出してください。</strong></p>
    <p>実際の OpenGL / OpenGL ES の描画命令の発行は、GLCommand クラスによって行われます。</p>
 */
class DrawBatch : public GMObject
{
public:    
    /*!
        @task   描画の開始と終了
     */
    
    /*!
        @method     Begin
     */
    static void     Begin() throw(GameInvalidOperationError);

    /*!
        @method     End
     */
    static void     End() throw(GameInvalidOperationError);

    static void     __FlushBatchDraws();

public:
    /*!
        @task   点の描画
     */
    
    /*!
        @method     DrawPoint
        @abstract   座標を指定して点を描画します。
        GL クラスの EnablePointSprite() メソッドを使用することにより、ポイントスプライトを有効化して使用することができます。
        ポイントスプライトに使用できる点のサイズには上限があります。
     */
    static void DrawPoint(const Vector2& pos, const Color& color, float size=1.0f) throw(GameInvalidOperationError);

    /*!
        @method     DrawPoint
        @abstract   座標を指定して点を描画します。
        GL クラスの EnablePointSprite() メソッドを使用することにより、ポイントスプライトを有効化して使用することができます。
        ポイントスプライトに使用できる点のサイズには上限があります。
     */
    static void DrawPoint(const Vector3& pos, const Color& color, float size=1.0f) throw(GameInvalidOperationError);

    
    /*!
        @task   線の描画
     */
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const Vector2& p1, const Vector2& p2, const Color& color, float width = 1.0f) throw(GameInvalidOperationError);
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const Vector2& p1, const Vector2& p2, const Color& color1, const Color& color2, float width = 1.0f) throw(GameInvalidOperationError);

    /*!
        @method     DrawLine
     */
    static void DrawLine(const Vector3& p1, const Vector3& p2, const Color& color, float width = 1.0f) throw(GameInvalidOperationError);
    
    /*!
        @method     DrawLine
     */
    static void DrawLine(const Vector3& p1, const Vector3& p2, const Color& color1, const Color& color2, float width = 1.0f) throw(GameInvalidOperationError);

    
    /*!
        @task   三角形の描画
     */

    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color = Color::white, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero) throw(GameInvalidOperationError);
    
    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& c1, const Color& c2, const Color& c3, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero) throw(GameInvalidOperationError);
    
    /*!
        @method     FillTriangle
     */
    static void FillTriangle(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& n1, const Vector3& n2, const Vector3& n3, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero) throw(GameInvalidOperationError);

    static void __FillTriangle(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& n1, const Vector3& n2, const Vector3& n3, const Color& c1, const Color& c2, const Color& c3, const Vector2& t1, const Vector2& t2, const Vector2& t3) throw(GameInvalidOperationError);
    
    /*!
        @task   四角形の描画
     */
    
    /*!
        @method     FillQuad
        @abstract   4点の頂点座標を指定して、四角形を描画します。
        <p>すべての頂点に共通の色を指定することができますが、ライティングが有効な環境下では有効になりません。</p>
        <p>各頂点のテクスチャ座標を指定することができますが、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, const Color& color = Color::white, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero, const Vector2& t4 = Vector2::zero) throw(GameInvalidOperationError);
    
    /*!
        @method     FillQuad
        @abstract   4点の頂点座標を指定して、四角形を描画します。
        <p>各頂点に個別の色を指定することができますが、ライティングが有効な環境下では有効になりません。</p>
        <p>各頂点のテクスチャ座標を指定することができますが、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, const Color& c1, const Color& c2, const Color& c3, const Color& c4, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero, const Vector2& t4 = Vector2::zero) throw(GameInvalidOperationError);

    /*!
        @method     FillQuad
        @abstract   4点の頂点座標、各頂点の法線ベクトル、テクスチャ座標を指定して、四角形を描画します。
        <p>テクスチャマッピングには、別途 GMBasicEffect クラスでのテクスチャの有効化とテクスチャ指定が必要です。</p>
     */
    static void FillQuad(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, const Vector3& n1, const Vector3& n2, const Vector3& n3, const Vector3& n4, const Vector2& t1 = Vector2::zero, const Vector2& t2 = Vector2::zero, const Vector2& t3 = Vector2::zero, const Vector2& t4 = Vector2::zero) throw(GameInvalidOperationError);

    static void __FillQuad(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4,
                         const Vector3& n1, const Vector3& n2, const Vector3& n3, const Vector3& n4,
                         const Color& c1, const Color& c2, const Color& c3, const Color& c4,
                         const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& t4) throw(GameInvalidOperationError);
    
};


#endif  //#ifndef __DRAW_BATCH_HPP__

