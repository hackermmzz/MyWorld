#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include"lightbase.h"
//////////////////////////////////////////////////
/*成员
struct DirectionalLight
 {
 vec3 direction;
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 };
*/
//////////////////////////////////////////////////
class DirectionalLight:virtual public LightBase
{
private:
    vec3 direction;
public:
    DirectionalLight(const vec3&direction,const vec3&ambient,const vec3&diffuse,const vec3&specular);
    void setdirection(const vec3&direction);
    vec3 getdirection(){return direction;}
    void apply_direction(Program&program,const char*structure_name);
    void apply(Program&program,const char*structure_name);
};

#endif // DIRECTIONALLIGHT_H
