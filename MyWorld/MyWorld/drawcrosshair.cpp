#include "drawcrosshair.h"
void DrawCrossHair()
{
    static bool init=0;
    static Vao*vao;
    static Vbo*vbo;
    static Program*program;
    if(!init)
    {
        init=1;
        vao=new Vao;
        GLfloat size=30;
        GLfloat pos[]{
            -size,0,size,0,
            0,size,0,-size
        };
        vbo=new Vbo(sizeof(pos),pos);
        vbo->setpoint(0,GL_FLOAT,2,sizeof(float)*2,0);
        vao->unbind();
        program=new Program("Src/Shader/CrossHair/CrossHair.vert","Src/Shader/CrossHair/CrossHair.frag");
    }
    api->glDisable(GL_DEPTH_TEST);
    program->bind();
    program->setfloat("width",window_width);
    program->setfloat("height",window_height);
    vao->bind();
    api->glDrawArrays(GL_LINES,0,4);
    api->glEnable(GL_DEPTH_TEST);
}
