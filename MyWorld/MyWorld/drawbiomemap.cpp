#include "drawbiomemap.h"
Texture2DGeneral*Biome_Map;
void DrawBiomeMap()
{
    static Program*program;
    static Vao*vao;
    static Vbo*vbo;
    static Ebo*ebo;
    static bool init=0;
    if(!init)
    {
        init=1;
        program=new Program("Src/Shader/BiomeMap/BiomeMap.vert","Src/Shader/BiomeMap/BiomeMap.frag");;
        Biome_Map=new Texture2DGeneral(BIOMEMAP_SIZE,BIOMEMAP_SIZE,GL_RGB,GL_RGB,GL_FLOAT,0);
        Biome_Map->filter(GL_LINEAR);
        Biome_Map->wrap(GL_CLAMP_TO_EDGE);
        vao=new Vao;
        vec4 pos_and_uv[4];
        float map_size=0.3;
        pos_and_uv[0]={-1,1,0,1};//左上
        pos_and_uv[1]=pos_and_uv[0]+vec4(map_size,0,1,0);//右上
        pos_and_uv[2]=pos_and_uv[1]+vec4(0,-map_size,0,-1);//右下
        pos_and_uv[3]=pos_and_uv[0]+vec4(0,-map_size,0,-1);//左下
        vbo=new Vbo(sizeof(pos_and_uv),pos_and_uv);
        vbo->setpoint(0,GL_FLOAT,2,sizeof(GLfloat)*4,0);
        vbo->setpoint(1,GL_FLOAT,2,sizeof(GLfloat)*4,sizeof(GLfloat)*2);
        GLuint indices[]{
            0,1,2,0,2,3
        };
        ebo=new Ebo(sizeof(indices)/sizeof(GLuint),indices);
        vao->unbind();
    }
    static ivec2 prePos = ivec2(INT_MAX,INT_MIN);
    if (prePos.equal(camera_chunk) == 0)
    {
        prePos = camera_chunk;
        UpdateBiomeMap();
    }
    api->glDisable(GL_DEPTH_TEST);
    api->glEnable(GL_BLEND);
    api->glBlendEquation(GL_FUNC_ADD);
    api->glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    vao->bind();
    program->bind();
    Biome_Map->bind(0);
    program->setint("BiomeMap",0);
    api->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    api->glEnable(GL_DEPTH_TEST);
    api->glDisable(GL_BLEND);
}

void UpdateBiomeMap()
{
    Biome_Map->bind();
    static int HALF_BIOMEMAP_SIZE=BIOMEMAP_SIZE/2;
    static vec3 data[BIOMEMAP_SIZE][BIOMEMAP_SIZE];
    for(int x=-HALF_BIOMEMAP_SIZE;x<=HALF_BIOMEMAP_SIZE;++x)
    {
        for(int z=-HALF_BIOMEMAP_SIZE;z<=HALF_BIOMEMAP_SIZE;++z)
        {
            ////////////////////////////////
            ivec2 position=ivec2(x,z)*SECTION_SIZE+camera_chunk;
            BiomeType biome;
            GenerateBiomeMap(position,biome);
            auto& pixel = data[x + HALF_BIOMEMAP_SIZE][z + HALF_BIOMEMAP_SIZE];
            if (biome == DESERT)pixel = vec3(0.5, 0.6, 0.0);
            else if (biome == SNOWFIELD)pixel = vec3(1.0, 1.0, 1.0);
            else if (biome == PLAIN)pixel = vec3(0.5, 0.5, 0);
            else if (biome == GRASSLAND)pixel = vec3(0, 0.5, 0);
            else if (biome == FOREST)pixel = vec3(0, 0.8, 0);
            else if (biome == RAINFOREST)pixel = vec3(0, 1, 0);
            else if (biome == OCEAN)pixel = vec3(0, 0, 1);
            ////////////////////////////////获取人物周围的生物群落
            if (abs(x) <= 1 && abs(z) <= 1)
                BiomeTypeAround[x + 1][z + 1] = biome;
        }
    }
    /////////////////对人物所在位置进行特殊着色
    static int weight = 3;
    for (int x = -weight; x <= weight; ++x)
    {
        for (int z = -weight; z <= weight; ++z) {
            data[HALF_BIOMEMAP_SIZE+x][HALF_BIOMEMAP_SIZE+z]= vec3(1, 0, 0);
        }
    }
    ////////////////
    api->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, BIOMEMAP_SIZE, BIOMEMAP_SIZE, GL_RGB, GL_FLOAT, data);
    Biome_Map->unbind();
}
