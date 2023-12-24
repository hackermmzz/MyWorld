#ifndef FBO_H
#define FBO_H
#include"Include.h"
#include"rbo.h"
#include"texture2dgeneral.h"
class Fbo
{
protected:
    GLuint id;
public:
    Fbo();
    Fbo(GLuint id);
    void bind();
    GLuint getid();
    void unbind();
    void setReadBuffer(GLenum BufferType=GL_NONE);
    void setDrawBuffer(GLenum BufferType=GL_NONE);
    void setDrawBuffers(GLuint BufferNum,GLenum*BufferType);
    void attachRbo(Rbo&rbo,GLenum attachment=GL_DEPTH_STENCIL_ATTACHMENT);
    void attachTexture(Texture2DGeneral&texture,GLenum attachment);
    void attachTexture(Texture2DGeneral& texture, GLenum attachment, GLenum textureTarget);
    void blitbuffer(GLuint id,GLuint src_width,GLuint src_height,GLuint dst_width,GLuint dst_height,GLbitfield mask=GL_COLOR_BUFFER_BIT);
    void blitbuffer(Fbo&fbo,GLuint src_width,GLuint src_height,GLuint dst_width,GLuint dst_height,GLbitfield mask=GL_COLOR_BUFFER_BIT);
    bool checkComplete();
    ~Fbo();
};

#endif // FBO_H
