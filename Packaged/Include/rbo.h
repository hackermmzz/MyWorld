#ifndef RBO_H
#define RBO_H
#include"Include.h"
class Rbo
{
private:
    GLuint id;
    GLuint width;
    GLuint height;
public:
    Rbo(GLuint width,GLuint height,GLenum type=GL_DEPTH24_STENCIL8,GLuint multisample=0);
    void bind();
    GLuint getid();
    void unbind();
    GLuint getwidth();
    GLuint getheight();
    ~Rbo();
};

#endif // RBO_H
