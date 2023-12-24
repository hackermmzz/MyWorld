#include "section.h"
//////////////////////////////////////////////
Ebo*Section::ebo;
//////////////////////////////////////////////
Section::Section()
{
    if(ebo==0)
    {
        Uint max_face_nums=SECTION_SIZE*SECTION_SIZE*SECTION_SIZE*6;
        ebo=new Ebo(max_face_nums*6,0);
        GLuint*ptr=(GLuint*)ebo->map(max_face_nums*6*sizeof(GLuint),0,GL_MAP_WRITE_BIT);
        for(int i=0;i<max_face_nums;++i)
        {
            int t=i*4;
            ptr[0]=t;
            ptr[1]=t+1;
            ptr[2]=t+2;
            ptr[3]=t;
            ptr[4]=t+2;
            ptr[5]=t+3;
            ptr+=6;
        }
        ebo->unmap();
        ebo->unbind();
    }
    vao=0;
    block_render=0;
    waterVao = 0;
    water_render = 0;
}

void Section::ResetState()
{
    IsFaceGenerateComplete=0;
    IsLoadFace = 0;
    IsFaceLoadToGpu=0;
}

void Section::PossDataToGpu()
{
    IsFaceLoadToGpu = 1;
    /////////////////////////////////////加载实体方块
    if(vao)delete vao;
    if(block_render)delete block_render;
    vao=new Vao();
    block_render=new Vbo(face.size()*sizeof(Face),face.data());
    block_render->setpoint(0,GL_FLOAT,3,sizeof(FaceVertex),0);
    block_render->setpoint(1,GL_FLOAT,3,sizeof(FaceVertex),sizeof(vec3));
    block_render->setpoint(2,GL_FLOAT,2,sizeof(FaceVertex),sizeof(vec3)*2);
    ebo->bind();
    vao->unbind();
    ///////////////////////////////////////加载水
    if (waterVao)delete waterVao;
    if (water_render)delete water_render;
    waterVao = new Vao;
    water_render = new Vbo(waterFace.size() * sizeof(Face),waterFace.data());
    water_render->setpoint(0, GL_FLOAT, 3, sizeof(FaceVertex), 0);
    water_render->setpoint(1, GL_FLOAT, 3, sizeof(FaceVertex), sizeof(vec3));
    water_render->setpoint(2, GL_FLOAT, 2, sizeof(FaceVertex), sizeof(vec3) * 2);
    ebo->bind();
    waterVao->unbind();
}

Section::~Section()
{
    if(vao)delete vao;
    if(block_render)delete block_render;
    if (waterVao)delete waterVao;
    if (water_render)delete water_render;
}
