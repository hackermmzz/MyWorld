#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include"Include.h"
#include"qopengltexture.h"
#include"texture2dgeneral.h"
#include"vao.h"
#include"vbo.h"
#include"ebo.h"
#include"program.h"
class Texture2D:public Texture2DGeneral
{
public:
   Texture2D(const char*file);
    static void DrawTexture2D(GLuint id=0);//if id==0,this function works as vao ,or it will render the texture
   ~Texture2D();
};

#endif // TEXTURE2D_H
