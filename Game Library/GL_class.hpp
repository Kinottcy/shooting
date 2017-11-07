//
//  GL_class.hpp
//  Game Framework
//
//  Created by numata on Sep 06, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GL_CLASS_HPP__
#define __GL_CLASS_HPP__

#include "GMObject.hpp"
#include "Color.hpp"
#include "Types.hpp"
#include "Texture.hpp"


extern float        gGMLineWidth;
extern float        gGMPointSize;


/*!
    @enum   BlendMode
    @group  Graphics

    @constant   BlendModeAlpha       アルファ合成
    @constant   BlendModeAdd         加算合成
    @constant   BlendModeClear       クリア合成
    @constant   BlendModeCopy        コピー合成
    @constant   BlendModeInvert      反転合成
    @constant   BlendModeMultiply    乗算合成
    @constant   BlendModeScreen      スクリーン合成
    @constant   BlendModeXOR         XOR合成
 */

enum BlendMode {
    BlendModeNone,
    BlendModeAlpha,
    BlendModeAdd,
    BlendModeClear,
    BlendModeCopy,
    BlendModeInvert,
    BlendModeMultiply,
    BlendModeScreen,
    BlendModeXOR,
};

std::string GetBlendModeName(BlendMode mode);


/*!
    @enum   GMPrimitiveType
    @group  Graphics
 
    @constant   GMPrimitiveTypePointList        点のリスト
    @constant   GMPrimitiveTypeLineList         線のリスト
    @constant   GMPrimitiveTypeLineStrip        連続した線のリスト
    @constant   GMPrimitiveTypeTriangleList     三角形のリスト
    @constant   GMPrimitiveTypeTriangleStrip    連続した三角形のリスト
 */
enum GMPrimitiveType {
    __GMPrimitiveTypeNone,
    GMPrimitiveTypePointList,
    GMPrimitiveTypeLineList,
    GMPrimitiveTypeLineStrip,
    GMPrimitiveTypeTriangleList,
    GMPrimitiveTypeTriangleStrip,
};

enum __GMVertexDataType {
    __GMVertexDataTypeVC,
    __GMVertexDataTypeVT,
    __GMVertexDataTypeVCT,
    __GMVertexDataTypeVNT,
    __GMVertexDataTypeVCNT,
};


/*!
    @struct     GMVertexDataVC
    @group      Graphics
 */
struct GMVertexDataVC {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    
};


/*!
    @struct     GMVertexDataVT
    @group      Graphics
 */
struct GMVertexDataVT {
    
    float       vx, vy, vz;
    float       tx, ty;
    
};

/*!
    @struct     GMVertexDataVCT
    @group      Graphics
 */
struct GMVertexDataVCT {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    float   tx, ty;
    
};

/*!
    @struct     GMVertexDataVNT
    @group      Graphics
 */
struct GMVertexDataVNT {
    
    float   vx, vy, vz;
    float   nx, ny, nz;
    float   tx, ty;
    
};

struct __GMVertexDataVCNT {
    
    float   vx, vy, vz;
    float   cr, cg, cb, ca;
    float   nx, ny, nz;
    float   tx, ty;
    
};


/*!
    @class  GL
    @group  Graphics
    @abstract OpenGL/OpenGL ESの命令を発行するためのクラスです。
    <p>アルファブレンディングやテクスチャの設定はこのクラスで管理しています。</p>
 */
class GL : public GMObject
{
    static BlendMode    sBlendMode;
    static bool         sIsDepthTestEnabled;
    static bool         sIsLightingEnabled;
    static bool         sIsPointSpriteEnabled;
    static bool         sIsScissorTestEnabled;
    static bool         sIsTextureEnabled;
    static Texture*     sTexture;
    static bool         sUsesWireframe;
    static Game::Rect   sViewportRect;

public:
    /*!
        @task   Static 関数
     */

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void     DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVC* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void     DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVT* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void     DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVCT* data, int startIndex, int primitiveCount);

    /*!
        @method     DrawPrimitivesUser
        @abstract   渡されたバッファに対して、頂点配列を使用した描画を行います。
     */
    static void     DrawPrimitivesUser(GMPrimitiveType type, GMVertexDataVNT* data, int startIndex, int primitiveCount);

    static void     __DrawPrimitivesUser(GMPrimitiveType type, __GMVertexDataVCNT* data, int startIndex, int primitiveCount);

    /*!
        @method     EnableDepthTest
     */
    static void     EnableDepthTest(bool enabled);
    
    /*!
        @method     EnableLight
     */
    static void     EnableLight(int lightIndex, bool enabled);

    /*!
        @method     EnableLighting
        @abstract   ライティングを有効または無効にします。
     */
    static void     EnableLighting(bool enabled);

    /*!
        @method     EnablePointSprite
     */
    static void     EnablePointSprite(bool enabled);
    
    /*!
        @method     EnableScissorTest
     */
    static void     EnableScissorTest(bool enabled);

    /*!
        @method     EnableTexture
     */
    static void     EnableTexture(bool enabled);
    
    /*!
        @method     EnableWireframeMode
     */
    static void     EnableWireframeMode(bool enabled);
    

    // ブレンドモードの設定
    //     cf. http://tobysoft.net/wiki/index.php?PhotoShop%2F%A5%EC%A5%A4%A5%E4%A1%BC%A4%CE%B7%D7%BB%BB%CA%FD%CB%A1%A4%CB%A4%C4%A4%A4%A4%C6
    //     cf. http://blog.jyoken.net/?eid=553888
    //     cf. http://d.hatena.ne.jp/keim_at_Si/20060210/p1
    //     cf. http://www.bea.hi-ho.ne.jp/gaku-iwa/color/conjn.html
    //     cf. http://www.simpelfilter.de/en/basics/mixmods.html
    
    /*!
        @method     GetBlendMode
        @abstract   現在のブレンドモードを取得します。
     */
    static BlendMode    GetBlendMode();

    /*!
        @method     GetTexture
     */
    static Texture*     GetTexture();

    /*!
        @method     GetViewport
     */
    static Game::Rect   GetViewport();
    
    /*!
        @method     IsDepthTestEnabled
     */
    static bool     IsDepthTestEnabled();

    /*!
        @method     IsLightingEnabled
        @abstract   ライティングを有効にしているかどうかを取得します。
     */
    static bool     IsLightingEnabled();

    /*!
        @method     IsPointSpriteEnabled
     */
    static bool     IsPointSpriteEnabled();
    
    /*!
        @method     IsScissorTestEnabled
     */
    static bool     IsScissorTestEnabled();

    /*!
        @method     IsTextureEnabled
     */
    static bool     IsTextureEnabled();

    /*!
        @method     IsWireframeModeEnabled
     */
    static bool     IsWireframeModeEnabled();
    

    /*!
        @method     SetBlendMode
        @abstract   ブレンドモードを設定します。
        <p>
            以下の値を指定することができます。
            <ul>
                <li>BlendModeAlpha（アルファ合成）</li>
                <li>BlendModeAdd（加算合成）</li>
                <li>BlendModeClear（クリア合成）</li>
                <li>BlendModeCopy（コピー合成）</li>
                <li>BlendModeInvert（反転合成）</li>
                <li>BlendModeMultiply（乗算合成）</li>
                <li>BlendModeScreen（スクリーン合成）</li>
                <li>BlendModeXOR（XOR合成）</li>
            </ul>
        </p>
     */
    static void     SetBlendMode(BlendMode mode);

    /*!
        @method     SetLightAmbientColor
     */
    static void     SetLightAmbientColor(int lightIndex, const Color& color);
    
    /*!
        @method     SetLightAttenuation
        @abstract 光の減衰率を指定します。
     */
    static void     SetLightAttenuation(int lightIndex, float constant, float linear, float quadratic);

    /*!
        @method     SetLightDiffuseColor
     */
    static void     SetLightDiffuseColor(int lightIndex, const Color& color);
    
    /*!
        @method     SetLightSpecularColor
     */
    static void     SetLightSpecularColor(int lightIndex, const Color& color);
    
    /*!
        @method     SetLightTypeAsPoint
        @abstract 位置を指定して点光源としてライトを設定します。
     */
    static void     SetLightTypeAsPoint(int lightIndex, const Vector3& vecPosition);
    
    /*!
        @method     SetLightTypeAsParallel
        @abstract 方向を指定して平行光源としてライトを設定します。
     */
    static void     SetLightTypeAsParallel(int lightIndex, const Vector3& vecDirection);
    
    /*!
        @method     SetLightTypeAsSpot
        @abstract 位置、方向、開き角度、拡散の度合いを指定して、スポットライトとしてライトを設定します。
        拡散の度合いを示す exponent には 0.0〜128.0 の値を指定します。
     */
    static void     SetLightTypeAsSpot(int lightIndex, const Vector3& vecPosition, const Vector3& vecDirection, float radAngle, float exponent);
    
    /*!
        @method     SetTexture
     */
    static void     SetTexture(Texture* tex);

    /*!
        @method     SetViewport
     */
    static void     SetViewport(const Game::Rect& rect);

};


#endif  //#ifndef __GL_CLASS_HPP__

