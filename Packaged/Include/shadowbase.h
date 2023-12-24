#ifndef SHADOWBASE_H
#define SHADOWBASE_H
#include"Include.h"
#include"fbo.h"
#include"texture2dgeneral.h"
#include"program.h"
class ShadowBase:public Fbo,public Texture2DGeneral
{
public:
    enum SHADOWTYPE{DIRECTIONALLIGHTSHADOW,POINTLIGHTSHADOW,SPOTLIGHTSHADOW};
private:
    Texture2DGeneral::Texture2DType  ParaseType(SHADOWTYPE type);
protected:
    vec3 position;
    Program*program;
public:
    ShadowBase(SHADOWTYPE type,const vec3&LightPosition,GLuint*width,GLuint*height,GLuint arraylevels);
    void bindTexture(GLuint index=0);
    void setPosition(const vec3&position);
    void setModel(Matrix&model);
    vec3  getPosition();
    void bind();
    Program* getProgram();
    ~ShadowBase();
};

#endif  //SHADOWBASE_H
