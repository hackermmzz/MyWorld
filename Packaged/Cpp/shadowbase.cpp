#include "Include/shadowbase.h"



Texture2DGeneral::Texture2DType ShadowBase::ParaseType(SHADOWTYPE type_)
{
    if(type_==DIRECTIONALLIGHTSHADOW)return TEXTURE2DARRAY;
    else if(type_==POINTLIGHTSHADOW)return CUBE;
    else if(type_==SPOTLIGHTSHADOW)return TEXTURE2D;
    return TEXTURE2D;
}

ShadowBase::ShadowBase(SHADOWTYPE type_, const vec3&LightPosition, GLuint *width_, GLuint *height_, GLuint arraylevels)
    :Fbo(),Texture2DGeneral(ParaseType(type_),width_,height_,SHADOW_DEPTHBUFFER_TYPE,GL_DEPTH_COMPONENT,GL_FLOAT,0,arraylevels,0)
{
    position=LightPosition;
    setReadBuffer(GL_NONE);
    setDrawBuffer(GL_NONE);
    wrap(GL_CLAMP_TO_BORDER);
    filter(GL_NEAREST);
    setBoarderColor({1.0});
    attachTexture(*this,GL_DEPTH_ATTACHMENT);
}
void ShadowBase::bindTexture(GLuint index)
{
    Texture2DGeneral::bind(index);
}

void ShadowBase::setPosition(const vec3 &position_)
{
    position=position_;
}

void ShadowBase::setModel(Matrix&model)
{
    program->setmat4("model",model);
}

vec3 ShadowBase::getPosition()
{
    return position;
}
void ShadowBase::bind()
{
    Fbo::bind();
    api->glClear(GL_DEPTH_BUFFER_BIT);
    fitViewport();
    program->bind();
}

Program *ShadowBase::getProgram()
{
    return program;
}
ShadowBase::~ShadowBase()
{}
