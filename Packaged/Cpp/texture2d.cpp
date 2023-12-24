#include "Include/texture2d.h"
Texture2D::Texture2D(const char*file):Texture2DGeneral(TEXTURE2D)
{
auto img=QImage(file).convertToFormat(QImage::Format_RGBA8888).mirrored(0,1);
width=new GLuint(img.width()),height=new GLuint(img.height());
api->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,*width,*height,0,GL_RGBA,GL_UNSIGNED_BYTE,img.bits());
wrap(GL_REPEAT);
filter(GL_LINEAR_MIPMAP_LINEAR);
api->glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::DrawTexture2D(GLuint id)
{
static Vao*vao;
static Vbo*vbo;
static Ebo*ebo;
static bool init=0;
static Program*program;
if(!init)
{
    init=1;
    vao=new Vao();
    GLfloat vertex[]{
        -1,1,0,1,
        1,1,1,1,
        -1,-1,0,0,
        1,-1,1,0
    };
    GLuint index[]{0,1,2,1,2,3};
    vbo=new Vbo(sizeof(vertex),vertex);
    vbo->setpoint(0,GL_FLOAT,2,sizeof(float)*4,0);
    vbo->setpoint(1,GL_FLOAT,2,sizeof(float)*4,sizeof(float)*2);
    ebo=new Ebo(6,index);
    vao->unbind();
    /////////////////////
    const char*vs="#version 330 core\n"
                     "layout(location=0)in vec2 pos\n;"
                     "layout(location=1)in vec2 uv;\n"
                     "out vec2 UV;\n"
                     "void main(){\n"
                     "gl_Position=vec4(pos,0.0,1.0);\n"
                     "UV=uv;\n"
                     "}";
    const char*fs="#version 330 core\n"
                     "in vec2 UV;\n"
                     "uniform sampler2D sampler;\n"
                     "void main(){\n"
                     "gl_FragColor=vec4(texture(sampler,UV).rgb,1.0);\n"
                     "}";
    program=new Program(vs,fs,1);
    /////////////////////
}
vao->bind();
if(id!=0)
{
    program->bind();
    api->glActiveTexture(GL_TEXTURE0);
    api->glBindTexture(GL_TEXTURE_2D,id);
}
api->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

Texture2D::~Texture2D()
{

}
