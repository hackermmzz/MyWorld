#ifndef OFFSCREENRENDER_H
#define OFFSCREENRENDER_H
#include"fbo.h"
#include"rbo.h"
#include"vao.h"
#include"vbo.h"
#include"ebo.h"
#include"program.h"
class OffScreenRender:public Fbo
{
private:
    Rbo*rbo;
    Texture2DGeneral*colorbuffer;
    bool is_HDR;
public:
    OffScreenRender(GLuint width,GLuint height,bool HDR=0,GLuint multisample=0);
    void bindTexture(GLuint index=0);
   GLuint get_textureid();
   GLuint getwidth();
   GLuint getheight();
   void Draw();
   void clear();
   ~OffScreenRender();
};

#endif // OFFSCREENRENDER_H
