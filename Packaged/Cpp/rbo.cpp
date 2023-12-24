#include "Include/rbo.h"

Rbo::Rbo(GLuint width_, GLuint height_, GLenum type, GLuint multisample)
{
    width=width_;
    height=height_;
    api->glGenRenderbuffers(1,&id);
    bind();
    ///////////////////////////
    if(multisample==0){
        api->glRenderbufferStorage(GL_RENDERBUFFER,type,width,height);
    }
    ///////////////////////////多重采样
    else
        api->glRenderbufferStorageMultisample(GL_RENDERBUFFER,multisample,type, width, height);
    ///////////////////////////
}

void Rbo::bind()
{
    api->glBindRenderbuffer(GL_RENDERBUFFER,id);
}

GLuint Rbo::getid()
{
    return id;
}

void Rbo::unbind()
{
    api->glBindRenderbuffer(GL_RENDERBUFFER,0);
}

GLuint Rbo::getwidth()
{
    return width;
}

GLuint Rbo::getheight()
{
    return height;
}

Rbo::~Rbo()
{
    if(id)
        api->glDeleteRenderbuffers(1,&id);
}
