//
//  RenderTarget.cpp
//  Game Framework
//
//  Created by numata on Sep 01, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "RenderTarget.hpp"
#include <OpenGL/OpenGL.h>


RenderTarget::RenderTarget(int width, int height) throw(GameInvalidOperationError, GameOutOfMemoryError)
    : Texture(width, height)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GetName());

    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GetName(), 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

RenderTarget::RenderTarget(int width, int height, TextureFormat format) throw(GameInvalidOperationError, GameOutOfMemoryError)
    : Texture(width, height, format)
{
    glBindTexture(GL_TEXTURE_2D, GetName());

    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GetName(), 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

RenderTarget::~RenderTarget()
{
    if (mFramebuffer) {
        glDeleteFramebuffers(1, &mFramebuffer);
        mFramebuffer = 0;
    }
}

GLuint RenderTarget::__getFramebuffer() const
{
    return mFramebuffer;
}


