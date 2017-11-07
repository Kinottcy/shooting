//
//  GMGraphics.hpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GM_GRAPHICS_HPP__
#define __GM_GRAPHICS_HPP__


#include "GMObject.hpp"
#include "Types.hpp"
#include "RenderTarget.hpp"


/*!
    @class      GMGraphics
    @group      Graphics
 */
class GMGraphics : public GMObject
{    
    
    GLuint          mCurrentMainFramebuffer;
    RenderTarget*   mRenderTarget;

public:
    GMGraphics();
    
public:
    /*!
        @task   画面のクリア
     */    
    
    /*!
        @task   レンダリング・ターゲットの操作（未実装）
     */
    /*!
        @method     getRenderTarget
     */
    RenderTarget*   getRenderTarget() const;

    /*!
        @method     setRenderTarget
        @abstract   レンダリングターゲットを設定します。NULL を指定すると、デフォルトのレンダリングターゲットが選択されます。
     */
    void    setRenderTarget(RenderTarget* target);

    
    /*!
        @task   各種設定
     */
    
    
public:
    void        __setCurrentMainFramebuffer(GLuint framebuffer);
    
};


#endif  //#ifndef __GM_GRAPHICS_HPP__


