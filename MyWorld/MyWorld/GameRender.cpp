#include"GameRender.h"
void GameRender()
{
    static auto* MainFbo = new Fbo(OpenglWidget->defaultFramebufferObject());
  ////////////////////////////////////绘制气候
    DrawClimate();
    ////////////////////////////////////得到g-buffer
    GBuffer->bind();
    auto& GBuffers = GBuffer->GetBuffers();
    GBuffers[0]->fitViewport();
    ////////////////////////////////////绘制区块
   auto& section_visible = FrustumCull();
   DrawSection(section_visible);
   /////////////////////////////////////绘制人物
   DrawRole();
   //////////////////////////////////////
   MainFbo->bind();
   api->glViewport(0,0,window_width, window_height);
   //////////////////////////////////////绘制Gbuffer
   DrawGbuffer();
   GBuffer->blitbuffer(*MainFbo,GBuffer->GetBufferWidth(), GBuffer->GetBufferHeight(), window_width,window_height,GL_DEPTH_BUFFER_BIT);
   ////////////////////////////////////////绘制水
   DrawWater(section_visible);
   /////////////////////////////////////绘制天空盒
   DrawSkyBox();
   /////////////////////////////////////绘制一些点精灵
   DrawSnow();
   DrawRain();
   DrawFireFly();
   //////////////////////////////////////绘制选中的block边框
   DrawBlockEdge();
   /////////////////////////////////////绘制高度图
   DrawBiomeMap();
   /////////////////////////////////////绘制准线
   DrawCrossHair();
   /////////////////////////////////////绘制人物一些信息
    DrawInfo();
}
