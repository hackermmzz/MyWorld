#include "Include/texture2dgeneral.h"
Texture2DGeneral::Texture2DGeneral(GLuint id_, GLenum type_)
{
    id=id_;
    type=type_;
}

Texture2DGeneral::Texture2DGeneral()
{
    api->glGenTextures(1,&id);
}

Texture2DGeneral::Texture2DGeneral(Texture2DType type_)
:Texture2DGeneral()
{
    if(type_==TEXTURE2D)type=GL_TEXTURE_2D;
    else if(type_==CUBE)type=GL_TEXTURE_CUBE_MAP;
    else if(type_==MULTISAMPLE)type=GL_TEXTURE_2D_MULTISAMPLE;
    else if(type_==TEXTURE2DARRAY)type=GL_TEXTURE_2D_ARRAY;
    api->glBindTexture(type,id);
}

Texture2DGeneral::Texture2DGeneral(Texture2DType texturetype, GLuint *width_, GLuint *height_, GLuint internalformat, GLenum format, GLenum type_,GLuint samples,GLuint arraylevels,void **data)
    :Texture2DGeneral(texturetype)
{
    /////////////type=GL_TEXTURE_2D
    if(type==GL_TEXTURE_2D)
    {
        width=new GLuint(*width_);
        height=new GLuint(*height_);
        api->glTexImage2D(type,0,internalformat,*width,*height,0,format,type_,(void*)data);
    }
    /////////////type=GL_TEXTURE_2D_MULTISAMPLE
    else if(type==GL_TEXTURE_2D_MULTISAMPLE)
    {
        width=new GLuint(*width_);
        height=new GLuint(*height_);
        api->glTexImage2DMultisample(type,samples,internalformat,*width,*height,GL_TRUE);
    }
    /////////////type=GL_TEXTURE_CUBE_MAP
    else if(type==GL_TEXTURE_CUBE_MAP)
    {
        width=new GLuint[6];
        height=new GLuint[6];
        for(unsigned int i=0;i<6;++i)
        {
            width[i]=width_[i];
            height[i]=height_[i];
            api->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,internalformat,width[i],height[i],0, format,type_,data?data[i]:0);
        }
    }
    ///////////////type=GL_TEXTURE_2D_ARRAY
    else if(type==GL_TEXTURE_2D_ARRAY)
    {
        width=new GLuint(*width_);
        height=new GLuint(*height_);
        api->glTexImage3D(type,0,internalformat,*width,*height,arraylevels,0,format,type_,(void*)data);
    }
    /////////////////////////////默认的过滤方式和环绕方式
    wrap(GL_REPEAT);
    filter(GL_NEAREST);
    
}

Texture2DGeneral::Texture2DGeneral(GLuint width_, GLuint height_, GLenum internalformat, GLenum format, GLenum type_, void *data)
    :Texture2DGeneral(TEXTURE2D,&width_,&height_,internalformat,format,type_,0,0,(void**)data)
{
}

Texture2DGeneral::Texture2DGeneral(GLuint width_, GLuint height_,GLuint internalformat,GLuint samples)
:Texture2DGeneral(MULTISAMPLE,&width_,&height_,internalformat,0,0,samples,0,0)
{}

Texture2DGeneral::Texture2DGeneral(const uvec6&width_,const uvec6&height_,GLuint internalformat,GLenum format,GLenum type_,void**data)
    :Texture2DGeneral(CUBE,width_.copy().value_ptr(),height_.copy().value_ptr(),internalformat,format,type_,0,0,data)
{}

Texture2DGeneral::Texture2DGeneral(GLuint width_, GLuint height_, GLenum internalformat, GLenum format, GLenum type_, GLuint levels, void *data)
    :Texture2DGeneral(TEXTURE2DARRAY,&width_,&height_,internalformat,format,type_,0,levels,(void**)data)
{}
void Texture2DGeneral::wrapX(GLint param)
{
    api->glTexParameteri(type, GL_TEXTURE_WRAP_S, param);
}

void Texture2DGeneral::wrapY(GLint param)
{
    api->glTexParameteri(type, GL_TEXTURE_WRAP_T, param);
}

void Texture2DGeneral::wrapZ(GLint param)
{
    api->glTexParameteri(type, GL_TEXTURE_WRAP_R, param);
}

void Texture2DGeneral::wrap(GLint param)
{
     api->glTexParameteri(type, GL_TEXTURE_WRAP_S, param);
     api->glTexParameteri(type, GL_TEXTURE_WRAP_T, param);
     if(type==GL_TEXTURE_CUBE_MAP)
     api->glTexParameteri(type, GL_TEXTURE_WRAP_R, param);
}

void Texture2DGeneral::filterMin(GLint filter)
{
     api->glTexParameteri(type, GL_TEXTURE_MIN_FILTER,filter);
}

void Texture2DGeneral::filterMag(GLint filter)
{
     api->glTexParameteri(type, GL_TEXTURE_MAG_FILTER,filter);
}

void Texture2DGeneral::filter(GLint filter)
{
        api->glTexParameteri(type, GL_TEXTURE_MIN_FILTER,filter);
        api->glTexParameteri(type, GL_TEXTURE_MAG_FILTER,filter);
}

void Texture2DGeneral::bind(GLuint index)
{
    api->glActiveTexture(GL_TEXTURE0+index);
    api->glBindTexture(type,id);
}

void Texture2DGeneral::bindImage(GLuint index, GLenum format, GLenum access)
{
bind(index);
api->glBindImageTexture(index,id,0,GL_FALSE,0,access,format) ;
}

void Texture2DGeneral::unbind()
{
    api->glBindTexture(type,0);
}

void Texture2DGeneral::setBoarderColor(const vec4 &color)
{
  api->glTexParameterfv(type, GL_TEXTURE_BORDER_COLOR, color.copy().value_ptr());
}

GLuint Texture2DGeneral::getwidth()
{
      return *width;
}

GLuint Texture2DGeneral::getheight()
{
      return *height;
}

void Texture2DGeneral::getwidth(GLuint *width_)
{
      if(type==GL_TEXTURE_CUBE_MAP)
          for(unsigned int i=0;i<6;++i)
              width_[i]=width[i];
      else
          *width_=*width;
}

void Texture2DGeneral::getheight(GLuint *height_)
{
      if(type==GL_TEXTURE_CUBE_MAP)
          for(unsigned int i=0;i<6;++i)
            height_[i]=height[i];
      else
          *height_=*height;
}

GLuint Texture2DGeneral::getid()
{
    return id;
}

GLuint Texture2DGeneral::preserve()
{
    GLuint temp=id;
    id=0;
    return temp;
}

GLenum Texture2DGeneral::getType()
{
    return type;
}

void Texture2DGeneral::fitViewport()
{
api->glViewport(0,0,*width,*height);
}

Texture2DGeneral::~Texture2DGeneral()
{
    if(id)api->glDeleteTextures(1,&id);
    //////////////////delete width and height
    if(type==GL_TEXTURE_CUBE_MAP)
    {
        delete []width;
        delete []height;
    }
    else if(type==GL_TEXTURE_2D||type==GL_TEXTURE_2D_MULTISAMPLE)
    {
        delete width;
        delete height;
    }
}
