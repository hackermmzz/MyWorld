#include "Include/spotlightshadow.h"


SpotLightShadow::SpotLightShadow(const vec3 &position_, GLuint size, const vec3 &direction_, double fov_,double near_,double far_)
    :ShadowBase(SPOTLIGHTSHADOW,position_,&size,&size,0)
{
    fov=fov_;
    direction=direction_.normalize();
    Far=far_;
    Near=near_;
    update();
}

void SpotLightShadow::setFov(double Fov)
{
    fov=Fov;
}

void SpotLightShadow::setDirection(const vec3 &direction_)
{
    direction=direction_.normalize();
}

void SpotLightShadow::bind()
{
    static bool init=0;
    if(!init)
    {
        init=1;
        /////////////////////////////////////
        const char*vertex="#version 420 core\n"
                             "layout(location=0)in vec3 pos;\n"
                             "uniform mat4 model;\n"
                             "uniform mat4 vp;"
                            "uniform vec3 position;"
                             "out vec3 FragToLight;\n"
                             "void main(void)\n"
                             "{\n"
                             "FragToLight=normalize(vec3(model*vec4(pos,1.0))-position);\n"
                             "gl_Position =vp*model*vec4(pos,1.0);\n"
                             "}\n";
        const char*fragment="#version 420 core\n"
                             "in vec3 FragToLight;\n"
                             "uniform vec3 direction;"//have been normalized
                             "uniform float cos_half_fov;"//the cos value of half_fov
                             "void main(void)\n"
                             "{"
                             "float theta=dot(FragToLight,direction);"
                               "if(theta-cos_half_fov<0)gl_FragDepth=1.0;"
                               "else gl_FragDepth=gl_FragCoord.z;"
                             "}\n";
        program=new Program(vertex,fragment,1);
        /////////////////////////////////////
    }
    ShadowBase::bind();
    program->setfloat("far",Far);
    program->setmat4("vp",vp);
    program->setvec3("position",position.value_ptr());
    program->setfloat("cos_half_fov",cos_half_fov);
    program->setvec3("direction",direction.value_ptr());
}

void SpotLightShadow::update()
{
    Matrix projection=Matrix::perspective(fov,getwidth()*1.0/getheight(),Near,Far);
    Matrix view_=Matrix::camera(position,position+direction,{0,1,0});
    view=view_;
    vp=projection*view;
    cos_half_fov=cos(fov*PI/360);
}

Matrix &SpotLightShadow::getViewMatrix()
{
    return view;
}

vec3 SpotLightShadow::getDirection()
{
    return direction;
}

double SpotLightShadow::getFar()
{
    return Far;
}

double SpotLightShadow::getNear()
{
    return Near;
}

Matrix &SpotLightShadow::getVpMatrix()
{
    return vp;
}

SpotLightShadow::~SpotLightShadow()
{

}
