#include "drawskybox.h"

void DrawSkyBox()
{
    static bool init=0;
    static Program*program;
    static Vao*vao;
    static Vbo*vbo;
    static Ebo*ebo;
    if(!init)
    {
        init=1;
        //////////////////////////////生成program
        program=new Program("Src/Shader/SkyBox/SkyBox.vert","Src/Shader/SkyBox/SkyBox.frag");
        //////////////////////////////
        float skyboxVertices[] = {
            1,1,1,
            1,1,-1,
            -1,1,-1,
            -1,1,1,
            1,-1,1,
            1,-1,-1,
            -1,-1,-1,
            -1,-1,1
        };
        GLuint indices[]={
            0,1,2,0,2,3,
            0,1,5,0,5,4,
            0,4,7,0,3,7,
            6,2,3,6,3,7,
            6,7,4,6,4,5,
            6,2,1,6,1,5
        };
        vao=new Vao();
        vbo=new Vbo(sizeof(skyboxVertices),skyboxVertices);
        vbo->setpoint(0,GL_FLOAT,3,sizeof(float)*3);
        ebo=new Ebo(36,indices);
        vao->unbind();
        //////////////////////////////
    }
    Matrix view=camera_view.ToMat3();
    api->glDepthFunc(GL_LEQUAL);
    program->bind();
    vao->bind();
    skybox->bind(0);
    program->setint("sampler",0);
    program->setmat4("view",view);
    program->setmat4("projection",camera_projection);
    api->glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    api->glDepthFunc(GL_LESS);
}
