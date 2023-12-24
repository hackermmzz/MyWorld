#include "Include/directionallight.h"


DirectionalLight::DirectionalLight(const vec3 &direction_, const vec3 &ambient_, const vec3 &diffuse_, const vec3 &specular_)
    :LightBase(ambient_,diffuse_,specular_),direction(direction_)
{}

void DirectionalLight::setdirection(const vec3 &direction_)
{
    direction=direction_;
}

void DirectionalLight::apply_direction(Program&program,const char*structure_name)
{
    program.setvec3(GENERATE_NAME(structure_name,DIRECTION),direction.value_ptr());
}

void DirectionalLight::apply(Program &program, const char*structure_name)
{
    LightBase::apply(program,structure_name);
    program.setvec3(GENERATE_NAME(structure_name,DIRECTION),direction.value_ptr());
}
