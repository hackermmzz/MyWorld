#include "DrawClimate.h"

void DrawClimate()
{
    static Fbo* fbo;
    static Program* program;
    static Vao* vao;
    static Texture2DGeneral* star;
    static bool init = 0;
    if (!init)
    {
        init = 1;
        ////////////////////////////////////////
        fbo = new Fbo();
        fbo->attachTexture(*skybox, GL_COLOR_ATTACHMENT0);
        fbo->setDrawBuffer(GL_COLOR_ATTACHMENT0);
        fbo->setReadBuffer(GL_COLOR_ATTACHMENT0);
        if (fbo->checkComplete() == 0)exit(0);
        fbo->unbind();
        ////////////////////////////////////////
        program = new Program("Src/Shader/Climate/Climate.vert", "Src/Shader/Climate/Climate.geom", "Src/Shader/Climate/Climate.frag");
        Matrix cameraMatrix[6];
        cameraMatrix[0] = Matrix::camera(vec3(0), vec3(1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));//positive x
        cameraMatrix[1] = Matrix::camera(vec3(0), vec3(-1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));//nagative x
        cameraMatrix[2] = Matrix::camera(vec3(0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));//positive y
        cameraMatrix[4] = Matrix::camera(vec3(0), vec3(0.0, 0.0, 1.0), vec3(0.0, -1.0, 0.0));//positive z
        cameraMatrix[5] = Matrix::camera(vec3(0), vec3(0.0, 0.0, -1.0), vec3(0.0, -1.0, 0.0));//nagative z
        for (int i=0;i<6;++i)
        {
            auto& mat = cameraMatrix[i];
            program->setmat4(("view[" + to_string(i) + "]").c_str(), mat);
        }
        vao = new Vao();
        vec3 point[] = {
            {-1,1,-1},{1,1,-1},{1,1,1},{-1,1,1},
            {-1,-1,-1},{1,-1,-1},{1,-1,1},{-1,-1,1},
        };
        vec4 data[] = {
        vec4{point[1],0},vec4{point[5],0},vec4{point[6],0},vec4{point[1],0},vec4{point[6],0},vec4{point[2],0},
        vec4{point[0],1},vec4{point[3],1},vec4{point[7],1},vec4{point[0],1},vec4{point[7],1},vec4{point[4],1},
        vec4{point[0],2},vec4{point[1],2},vec4{point[2],2},vec4{point[0],2},vec4{point[2],2},vec4{point[3],2},
        vec4{point[3],4},vec4{point[2],4},vec4{point[6],4},vec4{point[3],4},vec4{point[6],4},vec4{point[7],4},
        vec4{point[0],5},vec4{point[1],5},vec4{point[5],5},vec4{point[0],5},vec4{point[5],5},vec4{point[4],5}
        };
        auto* vbo = new Vbo(sizeof(data),data);
        vbo->setpoint(0, GL_FLOAT, 4, sizeof(float) * 4, 0);
        vao->unbind();
        ///////////////////////////////////
       const  GLuint size = 1024;
       vec3(*starData)[size] = new vec3[size][size];
        star = new Texture2DGeneral(size, size, GL_RGB, GL_RED, GL_FLOAT, 0);
        star->wrap(GL_CLAMP_TO_BORDER);
        star->filter(GL_NEAREST);
        star->setBoarderColor({ 0 });
        Random starRand;
        int starPL = 500;
        float colorDiv = 255.0;
        starRand.SetSeed(gettime());
        for (int x = 0; x < size; ++x)
        {
            for (int z = 0; z < size; ++z)
            {
                auto& data = starData[x][z];
                if (starRand.rand(0, starPL))data = vec3(0);
                else {
                    data.r = starRand.rand(0, 50) / colorDiv;
                    data.g = starRand.rand(0, 50) / colorDiv;
                    data.b = starRand.rand(100, 200) / colorDiv;
                }
            }
        }
        star->bind();
        api->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, size, GL_RGB, GL_FLOAT, starData);
        delete []starData;
    }
    ////////////////////////////////////////更新时间
    UpdateLight();
    ///////////////////////////////////////产生云的噪声贴图
    GenerateCloud();
    ////////////////////////////////////////绘制天空气候
    fbo->bind();
    skybox->fitViewport();
    api->glClear(GL_COLOR_BUFFER_BIT);
    program->bind();
    ///////////////////////////////
    program->setint("cloud", 0);
    program->setint("star", 1);
    cloud->bind(0);
    star->bind(1);
    program->setvec3("LightPos", SunPos);
    program->setvec3("Light",SunLight);
    program->setfloat("Brightness", Brightness);
    program->setfloat("StarBrightness", StarBrightness);
    ///////////////////////////////
    vao->bind();
    api->glDrawArrays(GL_TRIANGLES, 0, 30);

}

void DrawSnow()
{
    static Program* TransformProgram;
    static Program* SnowRenderProgram;
    static Texture1D* RandomTexture;
    static Texture2D* snowTexture;
    static ParticleSystem* snowSystem = 0;
    static const int SnowLauncherNums = 5000;
    static const int SnowMaxNums = 100000;
    static const int SnowBufferSize = SnowMaxNums * sizeof(SnowParticle);
    static const int SnowRenderRadius = 20;
    static  Random rand;
    static Vao* vao[2];
    static Vbo* vbo[2];
    static bool IsSnow =1;
    static long long TotalTime = 3 * 60 * 1000;
    static long long Time = 0;
    if (!snowSystem)
    {
        snowTexture = new Texture2D("Src/Img/block/snow.png");
        //////////////////////////////////////
        vector<SnowParticle>SnowLauncher(SnowLauncherNums);
        float MulFac = 100.0;
        rand.SetSeed(gettime());
        for (auto& launcher : SnowLauncher)
        {
            launcher.age = 0;
            launcher.type = 0.0;
            launcher.life = rand.rand(100, 1000);
            launcher.pos = vec3(
                rand.rand(-SnowRenderRadius * MulFac, SnowRenderRadius * MulFac) / MulFac,
                -10000.0,
                rand.rand(-SnowRenderRadius * MulFac, SnowRenderRadius * MulFac) / MulFac
            );
        }
        /////////////////////////////////////
        const GLuint randTextureSize = 256;
        vector<vec3>dir(randTextureSize);
        for (auto&dir_:dir)
        {
         dir_.x = rand.rand(-80, 80);
         dir_.z = rand.rand(-80, 80);
         dir_.y = rand.rand(-200, -100);
         dir_=dir_.normalize();
        }
        RandomTexture = new Texture1D(randTextureSize, GL_RGB16F, GL_RGB, GL_FLOAT, dir.data());
       //////////////////////////////////////////
        for (int i = 0; i < 2; ++i)
        {
            vao[i] = new Vao;
            vbo[i] = new Vbo(SnowBufferSize, 0);
            if (i==0)
                vbo[i]->setdata(SnowLauncherNums * sizeof(SnowParticle), SnowLauncher.data());
            vbo[i]->setpoint(0, GL_FLOAT, 3, sizeof(SnowParticle), 0);//type life age
            vbo[i]->setpoint(1, GL_FLOAT, 3, sizeof(SnowParticle),offsetof(SnowParticle,SnowParticle::pos));
            vbo[i]->setpoint(2, GL_FLOAT, 3, sizeof(SnowParticle),offsetof(SnowParticle, SnowParticle::dir));
            vao[i]->unbind();
        }
        /////////////////////////////////////////////
        snowSystem = new ParticleSystem(vao, vbo, SnowLauncherNums);
        /////////////////////////////////////////////
        TransformProgram = new Program("Src/Shader/Snow/Transform.vert", "Src/Shader/Snow/Transform.geom", vector<string>{ "type","life","age","pos","dir"});
        SnowRenderProgram = new Program("Src/Shader/Snow/Snow.vert", "Src/Shader/Snow/Snow.frag");
        SnowRenderProgram->setuniformblock("VP", CAMERA_UBO_BINDING);
    }
    /////////////////////////////////////////判断今天是否应该下雪
    Time += render_time;
    if (Time / TotalTime)
    {
        Time = 0;
        IsSnow = rand.rand(0, 2) ? 1 : 0;
    }
    if (IsSnow == 0)return;
    ////////////////////////////////////////////判断人物所处的生物群落是否应该绘制雪
    static float blur[3][3] = {
        {0.0625,0.125,0.0625},
        {0.125,0.25,0.125},
        {0.0625,0.125,0.0625}
    };
    float val = 0.0;
    for (int x = 0; x < 3; ++x)
    {
        for (int z = 0; z < 3; ++z)
        {
            val += blur[x][z] * (BiomeTypeAround[x][z] == SNOWFIELD);
        }
    }
    if (val < 0.25)return;
    ///////////////////////////////////////////
    TransformProgram->bind();
    TransformProgram->setint("random", 0);
    RandomTexture->bind(0);
    TransformProgram->setvec3("rolePos", camera.position);
    TransformProgram->setfloat("deltaTime", render_time);
    snowSystem->Update(GL_POINTS);
    /////////////////////////////////////////
    api->glEnable(GL_DEPTH_TEST);
    api->glEnable(GL_POINT_SPRITE);
    api->glEnable(GL_POINT_SMOOTH);
    api->glEnable(GL_PROGRAM_POINT_SIZE);
    api->glBindVertexArray(0);
    auto* RenderBuffer = snowSystem->GetCurrentRenderBuffer();
    RenderBuffer->bind();
    RenderBuffer->setpoint(0, GL_FLOAT, 3, sizeof(SnowParticle), offsetof(SnowParticle, SnowParticle::pos));
    SnowRenderProgram->bind();
    SnowRenderProgram->setint("snow", 0);
    SnowRenderProgram->setvec3("eye",camera.position);
    snowTexture->bind(0);
    snowSystem->Draw(GL_POINTS);
}

void DrawRain()
{
    static Program* TransformProgram;
    static Program* RainRenderProgram;
    static Texture1D* RandomTexture;
    static Texture2D* rainTexture;
    static ParticleSystem* rainSystem = 0;
    static const int rainLauncherNums = 2000;
    static const int rainDropMaxNums = 100000;
    static const int RainBufferSize = rainDropMaxNums * sizeof(RainParticle);
    static const int RainRenderRadius = 20;
    static Random rand;
    static Vao* vao[2];
    static Vbo* vbo[2];
    static bool IsRain = 0;
    static long long TotalTime = 3 * 60 * 1000;
    static long long Time = 0;
    if (!rainSystem)
    {
        rainTexture = new Texture2D("Src/Img/block/rain.png");
        //////////////////////////////////////
        vector<RainParticle>RainLauncher(rainLauncherNums);
        float MulFac = 100.0;
        rand.SetSeed(gettime());
        for (auto& launcher : RainLauncher)
        {
            launcher.age = 0;
            launcher.type = 0.0;
            launcher.life = rand.rand(100, 1000);
            launcher.pos = vec3(
                rand.rand(-RainRenderRadius * MulFac, RainRenderRadius * MulFac) / MulFac,
                -10000.0,
                rand.rand(-RainRenderRadius * MulFac, RainRenderRadius * MulFac) / MulFac
            );
        }
        /////////////////////////////////////
        const GLuint randTextureSize = 256;
        const int MulFac2 = 10000;
        vector<float>randNum(randTextureSize);
        for (auto& num : randNum)
        {
            num = rand.rand(0, MulFac2) * 1.0 / MulFac2;
        }
        RandomTexture = new Texture1D(randTextureSize, GL_R16F, GL_RED, GL_FLOAT, randNum.data());
        //////////////////////////////////////////
        for (int i = 0; i < 2; ++i)
        {
            vao[i] = new Vao;
            vbo[i] = new Vbo(RainBufferSize, 0);
            if (i == 0)
                vbo[i]->setdata(rainLauncherNums * sizeof(RainParticle), RainLauncher.data());
            vbo[i]->setpoint(0, GL_FLOAT, 3, sizeof(RainParticle), 0);//type life age
            vbo[i]->setpoint(1, GL_FLOAT, 3, sizeof(RainParticle), offsetof(RainParticle, RainParticle::pos));
            vao[i]->unbind();
        }
        /////////////////////////////////////////////
        rainSystem = new ParticleSystem(vao, vbo, rainLauncherNums);
        /////////////////////////////////////////////
        TransformProgram = new Program("Src/Shader/Rain/Transform.vert", "Src/Shader/Rain/Transform.geom", vector<string>{ "type", "life", "age", "pos"});
        RainRenderProgram = new Program("Src/Shader/Rain/Rain.vert", "Src/Shader/Rain/Rain.frag");
        RainRenderProgram->setuniformblock("VP", CAMERA_UBO_BINDING);
    }
    /////////////////////////////////////////////
    if (Time / TotalTime)
    {
        Time = 0;
        IsRain=rand.rand(0, 2) ? 1 : 0;
    }
    if (IsRain == 0)return;
    ////////////////////////////////////////////判断人物所处的生物群落是否应该绘制雪
    static float blur[3][3] = {
        {0.0625,0.125,0.0625},
        {0.125,0.25,0.125},
        {0.0625,0.125,0.0625}
    };
    float val = 0.0;
    for (int x = 0; x < 3; ++x)
    {
        for (int z = 0; z < 3; ++z)
        {
            val += blur[x][z] * (BiomeTypeAround[x][z] == FOREST);
        }
    }
    if (val < 0.25)return;
    ///////////////////////////////////////////
    TransformProgram->bind();
    TransformProgram->setint("random", 0);
    RandomTexture->bind(0);
    TransformProgram->setvec3("rolePos", camera.position);
    TransformProgram->setfloat("deltaTime", render_time);
    rainSystem->Update(GL_POINTS);
    /////////////////////////////////////////
    api->glEnable(GL_DEPTH_TEST);
    api->glEnable(GL_POINT_SPRITE);
    api->glEnable(GL_POINT_SMOOTH);
    api->glEnable(GL_PROGRAM_POINT_SIZE);
    auto* RenderBuffer = rainSystem->GetCurrentRenderBuffer();
    api->glBindVertexArray(0);
    RenderBuffer->bind();
    RenderBuffer->setpoint(0, GL_FLOAT, 3, sizeof(SnowParticle), offsetof(SnowParticle, SnowParticle::pos));
    RainRenderProgram->bind();
    RainRenderProgram->setint("rain", 0);
    RainRenderProgram->setvec3("eye", camera.position);
    rainTexture->bind(0);
    rainSystem->Draw(GL_POINTS);
}
