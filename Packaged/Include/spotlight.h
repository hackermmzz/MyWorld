#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
//////////////////////////////////////////////////
/*
struct SpotLight{
vec3 position;
vec3 direction;
float constant;//这个值固定为1,由宏确定,可有可无
float linear;
float quadratic;
float cutoff;
float outercutoff;
vec3 ambient;
vec3 diffuse;
vec3 specular;
 };
 */
/// ////////////////////////////////////////////////
#include "directionallight.h"
#include "pointlight.h"
class SpotLight:public DirectionalLight,public PointLight
{
private:
    float cutoff;
    float outercutoff;
public:
    SpotLight(const vec3&position,const vec3&direction,float linear,float quadratic,float cutoff,float outercutoff,const vec3&ambient,const vec3&diffuse,const vec3&specular);
    void setcutoff(float cutoff);
    void setoutercutoff(float outercutoff);
    vec3 getcutoff(){return cutoff;}
    vec3 getoutercutoff(){return outercutoff;}
    void apply_cutoff(Program&program,const char*structure_name);
    void apply_outercutoff(Program&program,const char*structure_name);
    void apply(Program&program,const char*structure_name);
};

#endif // SPOTLIGHT_H
