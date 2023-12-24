#ifndef SHADER_H
#define SHADER_H
#include"Include.h"
#include<qfile.h>
#include<qdir.h>
#include<qdatetime.h>
class Shader
{
  private:
    GLuint id;
public:
    Shader(const char*file,GLenum TYPE);
    Shader(const char*code,GLenum TYPE,GLboolean reserved);
    GLuint getid();
    static  void GetShaderError(const char*file,GLuint id);
    ~Shader();
};

#endif // SHADER_H
