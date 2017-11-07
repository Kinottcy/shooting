//
//  RenderTarget.hpp
//  Game Framework
//
//  Created by numata on Sep 01, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __RENDER_TARGET_HPP__
#define __RENDER_TARGET_HPP__


#include "Texture.hpp"
#include "GameError.hpp"


/*!
    @class  RenderTarget
    @group  Graphics
    @abstract レンダリングのターゲットとして使用できる2次元テクスチャを表すためのクラスです。
    GMGraphics クラスの setRenderTarget() メソッドで、このテクスチャをレンダリングの対象として設定することができます。
 */
class RenderTarget : public Texture
{
    GLuint  mFramebuffer;
    
public:
    /*!
        @task コンストラクタ
     */
    /*!
        @method     RenderTarget
        @abstract   幅と高さを指定して、32bit RGBA のレンダリングターゲットを作成します。
     */
    RenderTarget(int width, int height) throw(GameInvalidOperationError, GameOutOfMemoryError);

    /*!
        @method     RenderTarget2D
        @abstract   幅と高さとフォーマットを指定して、レンダリングターゲットを作成します。
     */
    RenderTarget(int width, int height, TextureFormat format) throw(GameInvalidOperationError, GameOutOfMemoryError);
    
    virtual ~RenderTarget();
    
public:
    GLuint  __getFramebuffer() const;
    
};


#endif  //#ifndef __RENDER_TARGET_HPP__

