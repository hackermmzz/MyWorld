#ifndef PROGRAM_H
#define PROGRAM_H
#include"shader.h"
#include"matrix.h"
class Program
{
protected:
    GLuint id;
public:
    Program(const char*vertex_code,const char*geometry_code,const char*fragment_code,GLboolean reserved);
    Program(const char*vertex_code,const char*fragment_code,GLboolean reserved);
    Program(const char *vertexfile, const char *fragfile);
    Program(const char*vertexfile,const char*geometryfile,const char*fragfile);
    Program(const char* vertexfile, const char* gemoetryfile, const vector<std::string>& varyings);
    Program(const char *programfile);
    Program(GLuint id);
     static bool compileprogram(const char *vertexfile, const char *fragfile,
                                 const char *tar);
     static bool geterror(GLuint id);
      void bind();
       void unbind();
       GLuint getid();
       static int getUniformlocation(const char *name, Program &id);
     void setfloat(const char *name, GLfloat val);
       void setvec2(const char *name, GLfloat val1, GLfloat val2);
      void setvec2(const char *name, GLfloat *val);
       void setvec2(const char *name, vec2&val);
      void setvec2(const char *name, vector<vec2>&val);
     void setvec3(const char *name, GLfloat *val);
    void setvec3(const char *name, GLfloat val1, GLfloat val2, GLfloat val3);
     void setvec3(const char *name, vec3&val);
    void setvec3(const char *name, vector<vec3>&val);
      void setivec3(const char *name, GLint *val);
      void setivec3(const char *name, ivec3&val);
      void setivec3(const char *name, vector<ivec3>&val);
      void setvec4(const char *name, GLfloat *val);
       void setvec4(const char *name, GLfloat val1, GLfloat val2, GLfloat val3,GLfloat val4);
      void setvec4(const char *name, vec4&val);
       void setvec4(const char *name,vector<vec4>&val);
      void setmat3(const char *name, GLfloat *val);
      void setmat4(const char *name, Matrix &mat);
      void setint(const char *name, GLint val);
      void setint(const char *name, vector<int>&val);
      void setuint(const char *name, GLuint val);
      void setuint(const char *name, vector<Uint>&val);
      void setuniformblock(const char *name, GLuint index);
      void setShaderStorageBlock(const char*name,GLuint index);
      ~Program();
};

#endif // PROGRAM_H
