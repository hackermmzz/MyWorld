#include "DrawFireFly.h"
void DrawFireFly()
{
    static Program* TransformProgram;
    static Program* FireFlyRenderProgram;
    static Texture1D* RandomTexture;
    static Texture1D* RandomTexture2;
    static Texture2D* FireFlyTexture;
    static ParticleSystem* FireFlySystem = 0;
    static const int FireFlyLauncherNums = 50;
    static const int FireFlyMaxNums = 500;
    static const int FireFlyBufferSize = FireFlyMaxNums * sizeof(FireFlyParticle);
    static const int FireFlyRenderRadius = 20;
    static  Random rand;
    static Vao* vao[2];
    static Vbo* vbo[2];
    if (!FireFlySystem)
    {
        FireFlyTexture = new Texture2D("Src/Img/FireFly/FireFly.png");
        //////////////////////////////////////
        vector<FireFlyParticle>SnowLauncher(FireFlyLauncherNums);
        float MulFac = 100.0;
        rand.SetSeed(gettime());
        for (auto& launcher : SnowLauncher)
        {
            launcher.age = 0;
            launcher.type = 0.0;
            launcher.life = rand.rand(100, 1000);
            launcher.pos = vec3(
                rand.rand(-FireFlyRenderRadius * MulFac, FireFlyRenderRadius * MulFac) / MulFac,
                -10000.0,
                rand.rand(-FireFlyRenderRadius * MulFac, FireFlyRenderRadius * MulFac) / MulFac
            );
        }
        /////////////////////////////////////
        const GLuint randTextureSize = 256;
        const int MulFac2 = 100;
        vector<float>randVal(randTextureSize);
        for (auto& val : randVal)
        {
            val = rand.rand(0, MulFac2)*1.0 /MulFac2;
        }
        RandomTexture = new Texture1D(randTextureSize, GL_R16F, GL_RED, GL_FLOAT, randVal.data());
        //////////////////////////////////////////
        const int MulFac3 = 100;
        const int HalfMulFac3 = MulFac3 / 2;
        vector<vec3>randVal2(randTextureSize);
        for (auto& val : randVal2)
        {
            val.x = rand.rand(-HalfMulFac3, HalfMulFac3) * 1.0 / MulFac3;
            val.y = rand.rand(-HalfMulFac3, HalfMulFac3) * 1.0 / MulFac3;
            val.z = rand.rand(-HalfMulFac3, HalfMulFac3) * 1.0 / MulFac3;
        }
        RandomTexture2 = new Texture1D(randTextureSize, GL_RGB16F, GL_RGB, GL_FLOAT, randVal2.data());
        //////////////////////////////////////////
        for (int i = 0; i < 2; ++i)
        {
            vao[i] = new Vao;
            vbo[i] = new Vbo(FireFlyBufferSize, 0);
            if (i == 0)
                vbo[i]->setdata(FireFlyLauncherNums * sizeof(FireFlyParticle), SnowLauncher.data());
            vbo[i]->setpoint(0, GL_FLOAT, 3, sizeof(FireFlyParticle), 0);//type life age
            vbo[i]->setpoint(1, GL_FLOAT, 3, sizeof(FireFlyParticle), offsetof(FireFlyParticle, FireFlyParticle::pos));
            vbo[i]->setpoint(2, GL_FLOAT, 3, sizeof(FireFlyParticle), offsetof(FireFlyParticle, FireFlyParticle::target));
            vao[i]->unbind();
        }
        /////////////////////////////////////////////
        FireFlySystem = new ParticleSystem(vao, vbo, FireFlyLauncherNums);
        /////////////////////////////////////////////
        TransformProgram = new Program("Src/Shader/FireFly/Transform.vert", "Src/Shader/FireFly/Transform.geom", vector<string>{ "type", "life", "age", "pos", "target"});
        TransformProgram->setShaderStorageBlock("PLANTS", FIREFLY_SSBO_BUFFER_BINDING);
        FireFlyRenderProgram = new Program("Src/Shader/FireFly/FireFly.vert", "Src/Shader/FireFly/FireFly.frag");
        FireFlyRenderProgram->setuniformblock("VP", CAMERA_UBO_BINDING);
    }
    ////////////////////////////////////////////判断当前时间是否允许出现萤火虫
    if (!(CurrentTime > 20.0 || CurrentTime <= 6.0))return;
    ////////////////////////////////////////////判断人物所处的生物群落是否应该绘制萤火虫
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
            auto& biome = BiomeTypeAround[x][z];
            if (biome == SAND || biome == SNOWFIELD)return;
            val += blur[x][z] * (biome == FOREST || biome == PLAIN || biome == GRASSLAND);
        }
    }
    if (val < 0.25)return;
    ///////////////////////////////////////////
    TransformProgram->bind();
    int plantNums = GetRoleAroundPlant();
    TransformProgram->setint("PlantNums", plantNums);
    TransformProgram->setint("random", 0);
    TransformProgram->setint("random2", 1);
    TransformProgram->setfloat("randVal", rand.rand(0, 100) / 100.0);
    RandomTexture->bind(0);
    RandomTexture2->bind(1);
    TransformProgram->setvec3("rolePos", camera.position);
    TransformProgram->setfloat("deltaTime", render_time);
    FireFlySystem->Update(GL_POINTS);
    /////////////////////////////////////////
    api->glEnable(GL_DEPTH_TEST);
    api->glEnable(GL_POINT_SPRITE);
    api->glEnable(GL_POINT_SMOOTH);
    api->glEnable(GL_PROGRAM_POINT_SIZE);
    api->glBindVertexArray(0);
    auto* RenderBuffer = FireFlySystem->GetCurrentRenderBuffer();
    RenderBuffer->bind();
    RenderBuffer->setpoint(0, GL_FLOAT, 3, sizeof(FireFlyParticle), offsetof(FireFlyParticle, FireFlyParticle::pos));
    FireFlyRenderProgram->bind();
    FireFlyRenderProgram->setint("FIreFly", 0);
    FireFlyRenderProgram->setvec3("eye", camera.position);
    FireFlyTexture->bind(0);
    FireFlySystem->Draw(GL_POINTS);
}

int GetRoleAroundPlant()
{
    static Ssbo* ssbo = 0;
    static const int MaxNum = 100;
    static const int MaxSize = MaxNum * sizeof(vec4);
    static const int SearchChunkArea =3;
    if (!ssbo)
    {
        ssbo = new Ssbo(MaxSize, 0);
        ssbo->bind_base(FIREFLY_SSBO_BUFFER_BINDING);
    }
    static Chunk* SearchChunk[SearchChunkArea * SearchChunkArea];
    static int loop = SearchChunkArea / 2;
    int index = 0;
    for (int x = -loop; x <= loop; ++x)
    {
        for (int z = -loop; z <= loop; ++z)
        {
            ivec2 pos = camera_chunk + ivec2(x, z) * SECTION_SIZE;
            SearchChunk[index] = world->getChunk(pos);
            if (SearchChunk[index] == 0)return 0;
            index++;
        }
    }
    //////////////////////////////////
    ssbo->bind();
    auto* buffer = (vec4*)ssbo->map(MaxSize, 0);
    buffer[0] = vec4(camera.position, 0.0);
    //////////////////////////////////
    static const int loop2 = SearchChunkArea * SearchChunkArea;
    int nums = 1;
    for (int i = 0; i < loop2; ++i)
    {
        auto& chunk = SearchChunk[i];
        auto& height = chunk->TerrainHeight;
        auto& block = chunk->Block;
        auto& biome = chunk->BiomeId;
        auto& pos = chunk->position;
        if (!(biome == FOREST || biome == PLAIN || biome == GRASSLAND))continue;
        for (int x = 0; x < SECTION_SIZE; ++x)
        {
            for (int z = 0; z < SECTION_SIZE; ++z)
            {
                auto height_ = height[x][z]+1;
                auto& id = block[x][height_][z].id;
                if (id == TALL_GRASS || id == SUN_FLOWER || id == MUSHROOM)
                {
                    buffer[nums++] = vec4(x + pos.x+0.5, height_+0.5, z + pos.y+0.5);
                }
                if (nums >= MaxNum)
                {
                    ssbo->unmap();
                    return nums;
                }
            }
        }
    }
    //////////////////////////////////
    ssbo->unmap();
    return nums;
}
