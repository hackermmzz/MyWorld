#ifndef POINTLIGHT_H
#define POINTLIGHT_H
////////////////////////////////////////////////////
/*
struct PointLight{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
*/
///////////////////////////////////////////////////////
#include"lightbase.h"
class PointLight:virtual public LightBase
{
private:
    vec3 position;
    float linear;
    float quadratic;
public:
    PointLight(const vec3&position,float linear,float quadratic,const vec3&ambient,const vec3&diffuse,const vec3&specular);
    void setposition(const vec3&position);
    void setlinear(float linear);
    void setquadratic(float quadratic);
    vec3 getposition(){return position;}
    float getlinear(){return linear;}
    float getquadratic(){return quadratic;}
    void apply_position(Program&program,const char*structure_name);
    void apply_linear(Program&program,const char*structure_name);
    void apply_quadratic(Program&program,const char*structure_name);
    void apply(Program&program,const char*structure_name);
};

#endif // POINTLIGHT_H
