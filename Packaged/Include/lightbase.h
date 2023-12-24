#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include"vec.hpp"
#include"program.h"
#include"Include.h"
#include<string.h>
using std::string;
/////////////////////////////////////////所有光源类型所包含的所有成员
/*
struct {
vec3 position;
vec3 direction;
float constant;//这个值固定为1,由宏确定
float linear;
float quadratic;
float cutoff;
float outercutoff;
vec3 ambient;
vec3 diffuse;
vec3 specular;
 };
*/
////////////////////////////////////////
class LightBase
{
private:
    vec3 ambient;
     vec3 diffuse;
    vec3 specular;
 protected:
    enum NAME_TYPE{
         POSITION,DIRECTION,CONSTANT,LINEAR,QUADRATIC,CUTOFF,OUTERCUTOFF,AMBIENT,DIFFUSE,SPECULAR};
    static char* GENERATE_NAME(const char*structure_name,NAME_TYPE type);
public:
    LightBase(const vec3&ambient,const vec3&diffuse,const vec3&specular);
    void apply_ambient(Program&program,const char*structure_name);
    void apply_diffuse(Program&program,const char*structure_name);
    void apply_specular(Program&program,const char*structure_name);
   virtual void apply(Program&program,const char*structure_name);
    void setambient(const vec3&ambient);
    void setdiffuse(const vec3&diffuse);
    void setspecular(const vec3&specular);
    vec3 getambient(){return ambient;}
    vec3 getdiffuse(){return diffuse;}
    vec3 getspecular(){return specular;}
};

#endif // LIGHTBASE_H
