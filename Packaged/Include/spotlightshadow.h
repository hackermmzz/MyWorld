#ifndef SPOTLIGHTSHADOW_H
#define SPOTLIGHTSHADOW_H

#include"shadowbase.h"
class SpotLightShadow:public ShadowBase
{
private:
    double fov;
    double cos_half_fov;
    vec3 direction;
    double Far;
    double Near;
    Matrix vp;
    Matrix view;
public:
    SpotLightShadow(const vec3&position,GLuint size,const vec3&direction,double fov,double Near,double Far);
    void setFov(double Fov);
    void setDirection(const vec3&direction);
    void bind();
    void update();
    Matrix &getVpMatrix();
    Matrix &getViewMatrix();
    vec3 getDirection();
    double  getFar();
    double getNear();
    ~SpotLightShadow();
};

#endif // SPOTLIGHTSHADOW_H
