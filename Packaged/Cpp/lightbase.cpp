#include "Include/lightbase.h"
char *LightBase::GENERATE_NAME(const char *structure_name, NAME_TYPE type)
{
    static char name[1024];
    ////////////////////////////////////////////
    const char*tail;
    switch (type) {
    case POSITION:
        tail=LIGHT_POSITION;
        break;
    case DIRECTION:
        tail=LIGHT_DIRECTION;
        break;
    case CONSTANT:
        tail=LIGHT_CONSTANT;
        break;
    case LINEAR:
        tail=LIGHT_LINEAR;
        break;
    case QUADRATIC:
        tail=LIGHT_QUADRATIC;
        break;
    case CUTOFF:
        tail=LIGHT_CUTOFF;
        break;
    case OUTERCUTOFF:
        tail=LIGHT_OUTERCUTOFF;
        break;
    case AMBIENT:
        tail=LIGHT_AMBIENT;
        break;
    case DIFFUSE:
        tail=LIGHT_DIFFUSE;
        break;
    case SPECULAR:
        tail=LIGHT_SPECULAR;
        break;
    }
    unsigned int index=0;
    while(structure_name[index])
    {
        name[index]=structure_name[index];
        index++;
    }
    name[index++]='.';
    unsigned int index2=0;
    while(tail[index2])
    {
        name[index]=tail[index2];
        index2++;
        index++;
    }
    name[index]=0;
    ////////////////////////////////////////////
    return name;
}

LightBase::LightBase( const vec3 &ambient_, const vec3 &diffuse_, const vec3 &specular_)
{
    ambient=ambient_;
    diffuse=diffuse_;
    specular=specular_;
}

void LightBase::apply_ambient(Program &program, const char*structure_name)
{
    program.setvec3(GENERATE_NAME(structure_name,AMBIENT),ambient.value_ptr());
}
void LightBase::apply_diffuse(Program &program, const char*structure_name)
{
    program.setvec3(GENERATE_NAME(structure_name,DIFFUSE),diffuse.value_ptr());
}

void LightBase::apply_specular(Program &program, const char*structure_name)
{
    program.setvec3(GENERATE_NAME(structure_name,SPECULAR),specular.value_ptr());
}

void LightBase::apply(Program&program, const char*structure_name)
{
     program.setvec3(GENERATE_NAME(structure_name,AMBIENT),ambient.value_ptr());
    program.setvec3(GENERATE_NAME(structure_name,DIFFUSE),diffuse.value_ptr());
     program.setvec3(GENERATE_NAME(structure_name,SPECULAR),specular.value_ptr());
}
void LightBase::setambient(const vec3 &ambient_)
{
    ambient=ambient_;
}

void LightBase::setdiffuse(const vec3 &diffuse_)
{
    diffuse=diffuse_;
}

void LightBase::setspecular(const vec3 &specular_)
{
    specular=specular_;
}
