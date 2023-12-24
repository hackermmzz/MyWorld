#include "drawcloud.h"

void DrawCloud()
{
    static bool init=0;
    static Vao*vao;
    static Vbo*vbo;
    static Ebo*ebo;
    static Fbo* fbo;
    if(!init)
    {
        init=1;
        ////////////////////////////////////////////
        vao=new Vao;
        GLfloat data[]{-1,1,0,1,1,1,1,1,1,-1,1,0,-1,-1,0,0};
        GLuint indices[]{0,1,2,0,2,3};
        vbo=new Vbo(sizeof(data),data);
        vbo->setpoint(0,GL_FLOAT,2,sizeof(GLfloat)*4,0);
        vbo->setpoint(1, GL_FLOAT, 2, sizeof(GLfloat) * 4, 2*sizeof(GLfloat));
        ebo=new  Ebo(6,indices);
        vao->unbind();
        /////////////////////////////////////////////
        fbo = new Fbo();
        fbo->attachTexture(*skybox, GL_COLOR_ATTACHMENT0);
        fbo->setDrawBuffer(GL_COLOR_ATTACHMENT0);
        if (fbo->checkComplete() == 0)exit(0);
        fbo->unbind();
    }
    GenerateCloud(); 
    fbo->bind();
    api->glViewport(0,0,skybox->getwidth(),skybox->getheight());
    api->glClear(GL_COLOR_BUFFER_BIT);
    vao->bind();
    CloudRenderProgram->bind();
    CloudRenderProgram->setint("cloud", 0);
    cloud->bind(0);
    api->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
