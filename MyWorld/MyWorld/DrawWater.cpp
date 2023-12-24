#include "DrawWater.h"
void DrawWater(vector<Section*>&sections)
{
    static int Time = 2000;
    static float currentTime = 0;
    currentTime += render_time;
    int binding = 0;
    api->glEnable(GL_DEPTH_TEST);
    WaterRenderProgram->bind();
    WaterRenderProgram->setvec3("camera", camera.position);
    WaterRenderProgram->setfloat("time", currentTime/Time);
    WaterRenderProgram->setint("skybox", binding);
    skybox->bind(binding++);
    auto& waves = GenerateWaveNoiseMap();
    WaterRenderProgram->setint("wave1", binding);
    waves[0]->bind(binding++);
    WaterRenderProgram->setint("wave2", binding);
    waves[1]->bind(binding++);
    //////////////////////////////////////°ó¶¨gbufferµÄ»º³å
    auto& gbuffer = GBuffer->GetBuffers();
    WaterRenderProgram->setint("screenColor",binding);
    gbuffer[0]->bind(binding++);
    WaterRenderProgram->setint("screenDepth", binding);
    gbuffer[1]->bind(binding++);
    /////////////////////////////////////
	for (auto& section : sections)
	{
        if (section->waterFace.size()==0)continue;
        /////////////////////////////////////////
        section->waterVao->bind();
        Face_Render_Nums += section->waterFace.size();
        api->glDrawElements(GL_TRIANGLES, 6 * section->waterFace.size(), GL_UNSIGNED_INT, 0);
	}
}

vector<Texture2DGeneral*>& GenerateWaveNoiseMap()
{
    static bool init = 0;
    static vector<Texture2DGeneral*>waves;
    if (!init)
    {
        init = 1;
        waves.push_back(new Texture2D("Src/Img/block/waterNormal1.jpg"));
        waves.push_back(new Texture2D("Src/Img/block/waterNormal2.jpg"));
        for (auto& wave : waves) {
            wave->bind();
            wave->wrap(GL_REPEAT);
        }
    }
    ///////////////////////////////////////////////
    return waves;
}

