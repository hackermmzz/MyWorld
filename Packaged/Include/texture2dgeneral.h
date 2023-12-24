#ifndef TEXTURE2DGENERAL_H
#define TEXTURE2DGENERAL_H
#include"Include.h"
#include"vec.hpp"
//////////////////////
////////////////////////
using uvec6=uvec<6>;
class Texture2DGeneral
{
public:
      enum Texture2DType{TEXTURE2D,CUBE,MULTISAMPLE,TEXTURE2DARRAY};
protected:
    GLenum type;
    GLuint id;
    GLuint *width;
    GLuint *height;
public:
    Texture2DGeneral();//only generate a texture id
    Texture2DGeneral(Texture2DType type);//only generate a texture id and bind it
    Texture2DGeneral(GLuint id,GLenum type);//accept an id and it's type
    Texture2DGeneral(GLuint width,GLuint height,GLenum internalformat,GLenum format,GLenum type,void*data);//only for texture2d
    Texture2DGeneral(GLuint width,GLuint height,GLuint internalformat,GLuint samples);//only for multisample
    Texture2DGeneral(const uvec6&width,const uvec6&height,GLuint internalformat,GLenum format,GLenum type,void**data);//only for cube
    Texture2DGeneral(GLuint width,GLuint height,GLenum internalformat,GLenum format,GLenum type,GLuint levels,void*data);//only for texture2darray
    Texture2DGeneral(Texture2DType texturetype,GLuint*width,GLuint*height,GLuint internalformat,GLenum format=0,GLenum type=0,GLuint samples=0,GLuint levels=0,void**data=0);//for all
    void wrapX(GLint wrap);
    void wrapY(GLint wrap);
    void wrapZ(GLint wrap);//only for cube
    void wrap(GLint wrap);
    void filterMin(GLint filter);
    void filterMag(GLint filter);
    void filter(GLint filter);
    void bind(GLuint index=0);
    void bindImage(GLuint index,GLenum format,GLenum access=GL_READ_WRITE);
    void unbind();
    void setBoarderColor(const vec4&color);
    GLuint getwidth();
    GLuint getheight();
    void getwidth(GLuint*width);
    void getheight(GLuint*height);
    GLuint getid();
    GLuint preserve();
    GLenum getType();
    void fitViewport();
    ~Texture2DGeneral();
};

#endif // TEXTURE2DGENERAL_H
