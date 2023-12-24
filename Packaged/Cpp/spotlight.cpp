#include "Include/spotlight.h"


SpotLight::SpotLight(const vec3 &position_, const vec3 &direction_, float linear_, float quadratic_, float cutoff_, float outercutoff_, const vec3 &ambient_, const vec3 &diffuse_, const vec3 &specular_)
    :LightBase(ambient_,diffuse_,specular_),
    DirectionalLight(direction_,ambient_,diffuse_,specular_)
    ,PointLight(position_,linear_,quadratic_,ambient_,diffuse_,specular_)
    ,cutoff(cutoff_),outercutoff(outercutoff_)
{}

void SpotLight::setcutoff(float cutoff_)
{
    cutoff=cutoff_;
}

void SpotLight::setoutercutoff(float outercutoff_)
{
    outercutoff=outercutoff_;
}

void SpotLight::apply_cutoff(Program &program,const char*structure_name)
{
   program.setfloat(GENERATE_NAME(structure_name,CUTOFF),cutoff);
}
void SpotLight::apply_outercutoff(Program &program, const char*structure_name)
{
    program.setfloat(GENERATE_NAME(structure_name,OUTERCUTOFF),outercutoff);
}
void SpotLight::apply(Program &program, const char*structure_name)
{
    PointLight::apply(program,structure_name);
    program.setvec3(GENERATE_NAME(structure_name,DIRECTION),getdirection().value_ptr());
    program.setfloat(GENERATE_NAME(structure_name,CUTOFF),cutoff);
    program.setfloat(GENERATE_NAME(structure_name,OUTERCUTOFF),outercutoff);
}
