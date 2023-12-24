#include "Include/pointlight.h"
PointLight::PointLight(const vec3 &position_,float linear_,float quadratic_,const vec3 &ambient_, const vec3 &diffuse_, const vec3 &specular_)
    :LightBase(ambient_,diffuse_,specular_),position(position_),linear(linear_),quadratic(quadratic_)
{}

void PointLight::setposition(const vec3 &position_)
{

    position=position_;
}

void PointLight::setlinear(float linear_)
{
    linear=linear_;
}

void PointLight::setquadratic(float quadratic_)
{
    quadratic=quadratic_;
}

void PointLight::apply_position(Program &program, const char*structure_name)
{
    program.setvec3(GENERATE_NAME(structure_name,POSITION),position.value_ptr());
}
void PointLight::apply_linear(Program &program, const char*structure_name)
{
    program.setfloat(GENERATE_NAME(structure_name,LINEAR),linear);
}

void PointLight::apply_quadratic(Program &program, const char*structure_name)
{
    program.setfloat(GENERATE_NAME(structure_name,QUADRATIC),quadratic);
}

void PointLight::apply(Program &program,const char*structure_name)
{
    LightBase::apply(program,structure_name);
    program.setvec3(GENERATE_NAME(structure_name,POSITION),position.value_ptr());
    program.setfloat(GENERATE_NAME(structure_name,LINEAR),linear);
    program.setfloat(GENERATE_NAME(structure_name,QUADRATIC),quadratic);
    program.setfloat(GENERATE_NAME(structure_name,CONSTANT),LIGHT_ATTENUATION_CONSTANT);
}
