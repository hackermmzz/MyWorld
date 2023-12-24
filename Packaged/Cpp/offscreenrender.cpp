#include "Include/offscreenrender.h"
OffScreenRender::OffScreenRender(GLuint width,GLuint height, bool HDR_, GLuint multisample)
    :Fbo()
{
    /////////////////////
    is_HDR=HDR_;
    GLenum format2=is_HDR?HDR_COLORBUFFER_TYPE:GL_RGB;
    if(multisample)
        colorbuffer=new Texture2DGeneral(width,height,format2,multisample);
    else colorbuffer=new Texture2DGeneral(width,height,format2,GL_RGB,GL_FLOAT,0);
    /////////////////////////////////
    colorbuffer->filter(GL_LINEAR);
  attachTexture(*colorbuffer,GL_COLOR_ATTACHMENT0);
    //////////////////////
    rbo=new Rbo(width,height,GL_DEPTH24_STENCIL8,multisample);
    //////////////////////
    attachRbo(*rbo,GL_DEPTH_STENCIL_ATTACHMENT);
    //////////////////////检查完整性
    if(!(api->glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE))
      qDebug()<<"ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
}

void OffScreenRender::bindTexture(GLuint index)
{
    colorbuffer->bind(index);
}

GLuint OffScreenRender::get_textureid()
{
    return colorbuffer->getid();
}

GLuint OffScreenRender::getwidth()
{
    return colorbuffer->getwidth();
}

GLuint OffScreenRender::getheight()
{
    return colorbuffer->getheight();
}

void OffScreenRender::Draw()
{
        static bool init=0;
        static Program*program;
        static Program*program_HDR;
        static Vao*vao;
        static Vbo*vbo;
        static Ebo*ebo;
        if(!init)
        {
            init=1;
            ///////////////////////////////生成program
            const char*vertex_scode="#version 330 core\n"
                                       "layout(location=0)in vec2 pos;\n"
                                       "layout(location=1)in vec2 uv;\n"
                                       "out vec2 UV;\n"
                                       "void main(void){\n"
                                       "gl_Position=vec4(pos,0.0,1.0);\n"
                                       "UV=uv;}";
            const char*frag_code="#version 330 core\n"
                                    "precision highp float;\n"
                                    "in vec2 UV;\n"
                                    "uniform sampler2D sampler;\n"
                                    "void main(void){\n"
                                    "vec3 color=texture(sampler,UV).rgb;"
                                    "gl_FragColor=vec4(color,1.0);}";
            GLuint vertex_id=api->glCreateShader(GL_VERTEX_SHADER);
            GLuint frag_id=api->glCreateShader(GL_FRAGMENT_SHADER);
            api->glShaderSource(vertex_id,1,&vertex_scode,0);
            api->glShaderSource(frag_id,1,&frag_code,0);
            api->glCompileShader(vertex_id);
            api->glCompileShader(frag_id);
            GLuint program_id=api->glCreateProgram();
            api->glAttachShader(program_id,vertex_id);
            api->glAttachShader(program_id,frag_id);
            api->glLinkProgram(program_id);
            api->glDeleteShader(frag_id);
            program=new Program(program_id);
            ///////////////////////////////
            const char*frag_code_HDR="#version 330 core\n"
                                    "precision highp float;\n"
                                    "in vec2 UV;\n"
                                    "uniform sampler2D sampler;\n"
                                    "void main(void){\n"
                                    "vec4 color=texture(sampler,UV);"
                                    "gl_FragColor=vec4(vec3(1.0)-exp(-color.rgb*1.0),1.0);}";
            frag_id=api->glCreateShader(GL_FRAGMENT_SHADER);
            api->glShaderSource(frag_id,1,&frag_code_HDR,0);
            api->glCompileShader(frag_id);
            program_id=api->glCreateProgram();
            api->glAttachShader(program_id,vertex_id);
            api->glAttachShader(program_id,frag_id);
            api->glLinkProgram(program_id);
            api->glDeleteShader(vertex_id);
            api->glDeleteShader(frag_id);
            program_HDR=new Program(program_id);
            Program::geterror(program_HDR->getid());
            ///////////////////////////////
            vao=new Vao();
            GLfloat vertex[]{-1,1,0,1,1,1,1,1,1,-1,1,0,-1,-1,0,0};
            GLuint index[]{0,1,3,1,2,3};
            vbo=new Vbo(sizeof(vertex),vertex);
            vbo->setpoint(0,GL_FLOAT,2,sizeof(float)*4);
            vbo->setpoint(1,GL_FLOAT,2,sizeof(float)*4,sizeof(float)*2);
            ebo=new Ebo(6,index);
            vao->unbind();
        }
        ///////////////////////////
        auto*program_=is_HDR?program_HDR:program;
        program_->bind();
        program_->setint("sampler",0);
        bindTexture(0);
        vao->bind();
        api->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void OffScreenRender::clear()
{
        api->glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}
OffScreenRender::~OffScreenRender()
{
if(rbo)delete rbo;
if(colorbuffer)delete colorbuffer;
}
