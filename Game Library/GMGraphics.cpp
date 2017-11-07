//
//  GMGraphics.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "GMGraphics.h"
#include <OpenGL/glu.h>


GMGraphics::GMGraphics()
{
    mRenderTarget = NULL;
}


#pragma mark -
#pragma mark <<<< レンダリング・ターゲットの操作 >>>>

RenderTarget* GMGraphics::getRenderTarget() const
{
    return mRenderTarget;
}

void GMGraphics::setRenderTarget(RenderTarget* target)
{
    mRenderTarget = target;
    
    if (mRenderTarget == NULL) {
        glBindFramebuffer(GL_FRAMEBUFFER, mCurrentMainFramebuffer);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, mRenderTarget->__getFramebuffer());
    }
}

void GMGraphics::__setCurrentMainFramebuffer(GLuint framebuffer)
{
    mCurrentMainFramebuffer = framebuffer;
}


