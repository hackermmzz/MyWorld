#ifndef DIRECTIONALLIGHTSHADOW_H
#define DIRECTIONALLIGHTSHADOW_H
#include"shadowbase.h"
#include"program.h"
#include <algorithm>
class DirectionalLightShadow:public ShadowBase
{
private:
    GLuint levels;
    Matrix*vp;
public:
    DirectionalLightShadow(const vec3&direction,GLuint width,GLuint height,GLuint levels,Matrix&projection,Matrix&view,const vec<DIRECTIONALLIGHTSHADOW_MAX_LEVEL>&percentage,float MulFactor=1.0);
    DirectionalLightShadow(const vec3&direction,GLuint width,GLuint height,GLuint levels);
    void update(Matrix&vp,const vec<DIRECTIONALLIGHTSHADOW_MAX_LEVEL>&percentage,float MulFactor=1.0);
    void update(Matrix&projection,Matrix&view,const vec<DIRECTIONALLIGHTSHADOW_MAX_LEVEL>&percentage,float MulFactor=1.0);
    void bind();
    GLuint getLevel();
    Matrix *getVpMatrix();
    void setDirection(const vec3&direction);
    ~DirectionalLightShadow();
};

#endif // DIRECTIONALLIGHTSHADOW_H
