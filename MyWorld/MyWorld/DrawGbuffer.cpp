#include "DrawGbuffer.h"

void DrawGbuffer()
{
	static Vao* vao = 0;
    static Fbo MainWindow(OpenglWidget->defaultFramebufferObject());
    static Texture2DGeneral* screen[2];
    static Texture2DGeneral* NormalTexture;
    static Texture2DGeneral* PositionTexture;
    static Fbo* fbo[2];
    if (!vao)
	{
        vao = new Vao();
        GLfloat vertex[]{
        -1,1,0,1,
        1,1,1,1,
        -1,-1,0,0,
        1,-1,1,0
        };
        GLuint index[]{ 0,1,2,1,2,3 };
        auto*vbo = new Vbo(sizeof(vertex), vertex);
        vbo->setpoint(0, GL_FLOAT, 2, sizeof(float) * 4, 0);
        vbo->setpoint(1, GL_FLOAT, 2, sizeof(float) * 4, sizeof(float) * 2);
        auto*ebo = new Ebo(6, index);
        vao->unbind();
        ///////////////////////////////
        fbo[0] = new Fbo();
        screen[0] = GBuffer->GetBuffers()[0];
        fbo[0]->attachTexture(*screen[0], GL_COLOR_ATTACHMENT0);
        fbo[0]->setDrawBuffer(GL_COLOR_ATTACHMENT0);
        ///////////////////////////////
        fbo[1] = new Fbo();
        screen[1] = new Texture2DGeneral(GBuffer->GetBufferWidth(), GBuffer->GetBufferHeight(), GL_RGB16F, GL_RGB, GL_FLOAT, 0);
        fbo[1]->attachTexture(*screen[1], GL_COLOR_ATTACHMENT0);
        fbo[1]->setDrawBuffer(GL_COLOR_ATTACHMENT0);
        /////////////////////////////////////
        NormalTexture = GBuffer->GetBuffers()[2];
        PositionTexture = GBuffer->GetBuffers()[1];
	}
    /////////////////////////////////////
    screen[0]->fitViewport();
    api->glDisable(GL_DEPTH_TEST);
    vao->bind();
    /////////////////////////////////////开始后期处理
    ////////////////////////炫光
    static Program* BloomProgram = 0;
    static Fbo* BloomFbo[2];
    static Texture2DGeneral* BloomTexture[2];
    if (!BloomProgram)
    {
        BloomProgram = new Program("Src/Shader/Bloom/Bloom.vert", "Src/Shader/Bloom/Bloom.frag");
        BloomFbo[0] = fbo[1];
        BloomTexture[0] = screen[1];
        BloomFbo[1] = new Fbo();
        BloomTexture[1] = new Texture2DGeneral(GBuffer->GetBufferWidth(), GBuffer->GetBufferHeight(), GL_RGB16F, GL_RGB, GL_FLOAT, 0);
        BloomFbo[1]->attachTexture(*BloomTexture[1], GL_COLOR_ATTACHMENT0);
        BloomFbo[1]->setDrawBuffer(GL_COLOR_ATTACHMENT0);
    }
    fbo[1]->bind();
    bool isHorizon = 1;
    BloomProgram->bind();
    BloomProgram->setint("screen", 0);
    BloomProgram->setint("horizon", isHorizon);
    screen[0]->bind(0);
    api->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    static const int BloomTime = 5;//必须为单数
    for (int i = 0; i < BloomTime; ++i)
    {
        BloomFbo[(i+1) % 2]->bind();
        isHorizon = !isHorizon;
        BloomProgram->setint("horizon", isHorizon);
        BloomTexture[i % 2]->bind(0);
        api->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
   //////////////混合+HDR
    static Program* HDR = 0;
    if (!HDR)
    {
        HDR = new Program("Src/Shader/HDR/HDR.vert", "Src/Shader/HDR/HDR.frag");
    }
    fbo[1]->bind();
    HDR->bind();
    HDR->setfloat("Brightness",Brightness);
    HDR->setfloat("exposure", exposure);
    HDR->setint("screen", 0);
    screen[0]->bind(0);
    HDR->setint("bloom", 1);
    BloomTexture[1]->bind(1);
    api->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    ////////////////ssao 由于Gbuffer未保存TBN矩阵,故不进行该处理
    ////////////////延时光照
    static Program* LightProgram = 0;
    if (!LightProgram)
    {
        LightProgram = new Program("Src/Shader/Light/Light.vert", "Src/Shader/Light/Light.frag");
        LightProgram->setShaderStorageBlock("LIGHTS", LIGHT_SSBO_BUFFER_BINDING);
    }
    fbo[0]->bind();
    LightProgram->bind();
    int LightNums = GeneratePointLightSsbo();
    LightProgram->setint("LightNums", LightNums);
    LightProgram->setint("screen", 0);
    LightProgram->setint("Position", 1);
    LightProgram->setint("Normal", 2);
    LightProgram->setfloat("Brightness", Brightness);
    screen[1]->bind(0);
    PositionTexture->bind(1);
    NormalTexture->bind(2);
    api->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //////////////////////////////////////
    MainWindow.bind();
    api->glViewport(0, 0, window_width, window_height);
    Texture2D::DrawTexture2D(screen[0]->getid());
}

int GeneratePointLightSsbo()
{
    static const int Ssbo_Max_Num = 1000;
    static const int Ssbo_Max_Size = sizeof(MyWorldPointLight) * Ssbo_Max_Num;
    static Ssbo* ssbo = 0;
    if (!ssbo)
    {
        ssbo = new Ssbo(Ssbo_Max_Size, 0);
        ssbo->bind_base(LIGHT_SSBO_BUFFER_BINDING);
    }
    //////////////////////////////////////
    ssbo->bind();
    auto*buffer=(MyWorldPointLight*)ssbo->map(Ssbo_Max_Size,0);
    int Nums = 0;
    for (auto itr = LightBlock.begin(); itr != LightBlock.end(); ++itr)
    {
        static vec3 points[8];
        static vec3 pointOffset[8] = {
            {0,0,0},{0,0,1},{0,1,0},{1,0,0},
            {0,1,1},{1,1,1},{1,0,1},{1,1,0}
        };
        auto& pos0 = itr->first;
        auto pos = vec3(pos0.x, pos0.y, pos0.z);
        for (int i = 0; i < 8; ++i)points[i] = pos+pointOffset[i];
        ////////////////////////////////
        bool flag = 1;
        for (int i = 0; i < 6; ++i)
        {
            if (JudgeBoxIsInSamePlane(points, camera_face[i]) == -1)
            {
                flag = 0;
                break;
            }
        }
        if (flag||(pos-camera.position).distance()<10)
        {
            buffer[Nums++] = {pos+vec3(0.5),GetLightBlockColor(itr->second)};
        }
        ////////////////////////////////////////////////
    }
    //////////////////////////////////////
    ssbo->unmap();
    return Nums;
}

vec3 GetLightBlockColor(Block& block)
{
    switch (block.id)
    {
    case TORCH:
        return vec3(1.0, 0.0, 0.0);
    case LIGHTSTONE:
        return vec3(1.0, 0.0, 1.0);
    }
}
