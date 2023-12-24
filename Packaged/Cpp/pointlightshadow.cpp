#include "Include/pointlightshadow.h"

PointLightShadow::PointLightShadow(GLuint size, const vec3 position_, double Near_, double Far_)
    :ShadowBase(POINTLIGHTSHADOW,position_,uvec6{size}.value_ptr(),uvec6{size}.value_ptr(),0)
{
    Far=Far_;
    Near=Near_;
    update();
}

void PointLightShadow::update()
{
    Matrix projection=Matrix::perspective(90.0,getwidth()*1.0/getheight(),Near,Far);
    vp[0]=projection*Matrix::camera(position, position +vec3(1.0,0.0,0.0), vec3(0.0,-1.0,0.0));//positive x
    vp[1]=projection*Matrix::camera(position, position +vec3(-1.0,0.0,0.0), vec3(0.0,-1.0,0.0));//nagative x
    vp[2]=projection*Matrix::camera(position, position +vec3(0.0,1.0,0.0), vec3(0.0,0.0,1.0));//positive y
    vp[3]=projection*Matrix::camera(position, position +vec3(0.0,-1.0,0.0), vec3(0.0,0.0,-1.0));//nagative y
    vp[4]=projection*Matrix::camera(position, position +vec3(0.0,0.0,1.0), vec3(0.0,-1.0,0.0));//positive z
    vp[5]=projection*Matrix::camera(position, position +vec3(0.0,0.0,-1.0), vec3(0.0,-1.0,0.0));//nagative z
}

void PointLightShadow::setFar(double Far_)
{
    Far=Far_;
}

void PointLightShadow::setNear(double Near_)
{
    Near=Near_;
}

Matrix *PointLightShadow::getVpMatrix()
{
    return vp;
}

void PointLightShadow::bind()
{
    static bool init=0;
    if(!init)
    {
        init=1;
        ////////////////////////
        const char*vert="#version 420 core\n"
                           "layout(location=0)in vec3 pos;\n"
                           "uniform mat4 model;\n"
                           "void main(void)\n"
                           "{\n"
                           "    gl_Position =model*vec4(pos,1.0);\n"
                           "}\n";
        const char*geom="#version 420 core\n"
                           "layout(triangles)in;\n"
                           "layout(triangle_strip,max_vertices=18)out;\n"
                           "uniform mat4 vp[6];\n"
                           "uniform vec3 lightpos;\n"
                           "out vec3 fragpos;\n"
                           "void main(void)\n"
                           "{\n"
                           "for(int i=0;i<6;++i)\n"
                           "{\n"
                           "gl_Layer=i;\n"
                           "for(int t=0;t<3;++t)\n"
                           "{\n"
                           "fragpos=vec3(gl_in[t].gl_Position);\n"
                           "gl_Position=vp[i]*gl_in[t].gl_Position;\n"
                           "EmitVertex();\n"
                           "}\n"
                           "EndPrimitive();\n"
                           "}\n"
                           "}\n";
        const char*frag="#version 420 core\n"
                           "uniform vec3 lightpos;\n"
                           "uniform float far;\n"
                           "in vec3 fragpos;\n"
                           "void main(void)\n"
                           "{\n"
                           "float dis=length(fragpos-lightpos);\n"
                           "gl_FragDepth=dis/far;\n"
                           "}\n";
        program=new Program(vert,geom,frag,1);
        ////////////////////////
    }
    ShadowBase::bind();
    for(int i=0;i<6;++i)
    program->setmat4(("vp["+std::to_string(i)+"]").c_str(),vp[i]);
    program->setfloat("far",Far);
    program->setvec3("lightpos",position.value_ptr());
}
PointLightShadow::~PointLightShadow()
{
}
