#include "Include/fbo.h"
Fbo::Fbo()
{
    api->glGenFramebuffers(1,&id);
    bind();
}

Fbo::Fbo(GLuint id_)
{
    id=id_;
    bind();
}

void Fbo::bind()
{
   api->glBindFramebuffer(GL_FRAMEBUFFER,id);
}

GLuint Fbo::getid()
{
   return id;
}
void Fbo::unbind()
{
   api->glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Fbo::setReadBuffer(GLenum BufferType)
{
   api->glReadBuffer(BufferType);
}

void Fbo::setDrawBuffer(GLenum BufferType)
{
   api->glDrawBuffer(BufferType);
}

void Fbo::setDrawBuffers(GLuint BufferNum, GLenum *BufferType)
{
   api->glDrawBuffers(BufferNum,BufferType);
}

void Fbo::attachRbo(Rbo &rbo,GLenum attachment)
{
   api->glFramebufferRenderbuffer(GL_FRAMEBUFFER,attachment,GL_RENDERBUFFER,rbo.getid());
}

void Fbo::attachTexture(Texture2DGeneral&texture,GLenum attachment)
{
   api->glFramebufferTexture(GL_FRAMEBUFFER,attachment,texture.getid(),0);
}

void Fbo::attachTexture(Texture2DGeneral& texture, GLenum attachment, GLenum textureTarget)
{
    api->glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, texture.getid(), 0);
}

void Fbo::blitbuffer(GLuint id_, GLuint src_width, GLuint src_height, GLuint dst_width, GLuint dst_height, GLbitfield mask)
{
   api->glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
   api->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id_);
   api->glBlitFramebuffer(0, 0, src_width, src_height, 0, 0, dst_width, dst_height, mask, GL_NEAREST);
}

void Fbo::blitbuffer(Fbo &fbo, GLuint src_width, GLuint src_height, GLuint dst_width, GLuint dst_height, GLbitfield mask)
{
   blitbuffer(fbo.getid(),src_width,src_height,dst_width,dst_height,mask);
}
bool Fbo::checkComplete()
{
   if(!(api->glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE))
       return 0;
   return 1;
}
Fbo::~Fbo()
{
    if(id)
      api->glDeleteFramebuffers(1,&id);
}
