#ifndef POINTLIGHTSHADOW_H
#define POINTLIGHTSHADOW_H
#include"shadowbase.h"
#include"matrix.h"
#include"program.h"
#include"string"
///////////////////////////////////////
///when use this class,you only need pass a program .Notice that the program should include 3 parts
/// each of them is vertexshader geometryshader and fragmentshader
/// vertexshader should include a uniform matrix4*4 named model
/// geometryshader should include a uniform matrix4*4 array  named vp[6]
/// and the fragmentshader should include a uniform vec3 called lightpos and a uniform float named far
/// that's all
//////////////////////////////////////
//////////////////////////////////////
class PointLightShadow:public ShadowBase
{
private:
    double Near;
    double Far;
    Matrix vp[6];
public:
    PointLightShadow(GLuint size,const vec3 position,double Near,double Far);
    void setFar(double Far);
    void setNear(double Near);
    Matrix* getVpMatrix();
    void bind();
    void update();
    ~PointLightShadow();
};

#endif // POINTLIGHTSHADOW_H
