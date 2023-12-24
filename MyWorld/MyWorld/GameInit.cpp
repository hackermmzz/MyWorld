#include"GameInit.h"
void GameInit()
{
    /////////////////////初始化camera_ubo
    camera_ubo=new Ubo(sizeof(Matrix)*3,0);
    camera_ubo->bind_base(CAMERA_UBO_BINDING);
    /////////////////////初始化所有着色器
    InitChunkRenderProgram();
    InitCloudRenderProgram();
    InitWaterRenderProgram();
    InitGBuffer();
    //////////////////////初始化所有噪声产生器
    InitNoiseGenerator();
    //////////////////////初始化所有的block类型
    InitBlock();
    //////////////////////初始化背包
    BagInit();
    /////////////////////初始化world
    world=new World;
    threadPool=world->threadpool;
    /////////////////////加载所有的chunk
    InitWorld();
    ////////////////////加载该区域的云朵
    InitCloud();
    /////////////////////加载天空盒
    GLuint skyboxDefaultSize = 1024;
    skybox=new Texture2DGeneral(uvec6(skyboxDefaultSize),uvec6(skyboxDefaultSize), GL_RGB, GL_RGB, GL_FLOAT,0);
    skybox->wrap(GL_CLAMP_TO_EDGE);
    skybox->filter(GL_NEAREST);
    /////////////////////初始化人物
    InitRole();
}
void InitNoiseGenerator()
{
    ////////////////////////////////////////////
    ContinentalNoise = PerlinNoise(WORLD_DEFAULT_SEED - INT_MAX / 2);
    ///////////////////////////////////////////
    ErosionNoise = PerlinNoise(WORLD_DEFAULT_SEED * WORLD_DEFAULT_SEED);
    //////////////////////////////////////////
    PeaksNoise = PerlinNoise(sqrt(WORLD_DEFAULT_SEED));
    ///////////////////////////////////////////
    HumidityNoise = PerlinNoise(WORLD_DEFAULT_SEED + WORLD_DEFAULT_SEED);
   ///////////////////////////////////////////
    TemperatureNoise = PerlinNoise(WORLD_DEFAULT_SEED +INT_MAX/2);
}

void InitChunkRenderProgram()
{
    BlockRenderProgram=new Program("Src/Shader/TerrianRender/TerrianRender.vert","Src/Shader/TerrianRender/TerrianRender.frag");
    BlockRenderProgram->setfloat("FrogMaxDis",FROG_MAX_DISTANCE);
    BlockRenderProgram->setfloat("FrogMinDis",FROG_MIN_DISTANCE);
    BlockRenderProgram->setuniformblock("VP", CAMERA_UBO_BINDING);
}

void InitWorld()
{
    /////////////////////////////////////
    int HALF_CHUNK_LOAD_SIZE=CHUNK_LOAD_SIZE/2;
    int HALF_CHUNK_RENDER_SIZE = CHUNK_RENDER_SIZE/2;
    ///////////////////////////////////生成世界
    queue<Chunk*>IsChunkLoadComplete;
    for(int x=-HALF_CHUNK_LOAD_SIZE;x<=HALF_CHUNK_LOAD_SIZE;++x)
    {
        for(int z=-HALF_CHUNK_LOAD_SIZE;z<=HALF_CHUNK_LOAD_SIZE;++z)
        {
            auto*chunk=world->getChunk(ivec2{x*SECTION_SIZE,z*SECTION_SIZE}+camera_chunk);
            chunk->ResetState();
            chunk->IsLoadBlock = 1;
            chunk->IsLoadChunk = 1;
            for (auto& section : chunk->section)section->ResetState();//初始化section
            IsChunkLoadComplete.push(chunk);
            threadPool->append([=](){
                GenerateTerrain(chunk);
                GenerateBlock(chunk);
            });
           }
        }
    /////////////////////////////////////等待所有的chunk加载完成
    while (!IsChunkLoadComplete.empty())
    {
        if (IsChunkLoadComplete.front()->IsBlockGenerateComplete == 1)
            IsChunkLoadComplete.pop();
    }
    //////////////////////////////////////生成装饰
    queue<Chunk*>IsDecorationGenerateComplete;
    for (int x = -HALF_CHUNK_RENDER_SIZE; x <= HALF_CHUNK_RENDER_SIZE; ++x)
    {
        for (int z = -HALF_CHUNK_RENDER_SIZE; z <= HALF_CHUNK_RENDER_SIZE; ++z)
        {
            auto* chunk = world->getChunk(ivec2{ x * SECTION_SIZE,z * SECTION_SIZE } + camera_chunk);
            chunk->IsLoadDecoration = 1;
            IsDecorationGenerateComplete.push(chunk);
                threadPool->append([=]() {
                    GenerateDecoration(chunk);
                    });
        }
    }
    ///////////////////////////////////////检测是否完成
    while (!IsDecorationGenerateComplete.empty())
    {
        if (IsDecorationGenerateComplete.front()->IsDecorationGenerateComplete)
            IsDecorationGenerateComplete.pop();
    }
    //////////////////////////////////////生成face
    queue<Section*>IsFaceGenerateComplete;
    for (int x = -HALF_CHUNK_RENDER_SIZE; x <= HALF_CHUNK_RENDER_SIZE; ++x)
    {
        for (int z = -HALF_CHUNK_RENDER_SIZE; z <= HALF_CHUNK_RENDER_SIZE; ++z)
        {
            auto* chunk = world->getChunk(ivec2{ x * SECTION_SIZE,z* SECTION_SIZE } + camera_chunk);
            auto cnc = GetChunkNearChunks(chunk);
            for (int i = 0; i < CHUNK_SIZE; ++i)
            {
                auto* section=chunk->section[i];
                section->IsLoadFace = 1;
                IsFaceGenerateComplete.push(section);
                threadPool->append([=]() {
                    GenerateFace(section,cnc);
                    });
            }
        }
    }
   //////////////////////////////////等待face产生完成
    while (!IsFaceGenerateComplete.empty())
    {
        if (IsFaceGenerateComplete.front()->IsFaceGenerateComplete)
        {
            auto* section = IsFaceGenerateComplete.front();
            section->PossDataToGpu();
            IsFaceGenerateComplete.pop();
        }
    }  
}

void InitBlock()
{
    ///////////////////////////////////加载block纹理集
    BLOCK_TEXTURE=new Texture2D("Src/Img/block/terrain.png");
    ///////////////////////////////////
    static vec2 PAD=vec2(1.0/FaceNumsPerAxis.x,1.0/FaceNumsPerAxis.y);
    static vec3 PointOffset[]{{0,1,0},{1,1,0},{1,1,1},{0,1,1},{0,0,0},{1,0,0},{1,0,1},{0,0,1}};
    static vec3 Normal[]{{0,1,0},{0,-1,0},{0,0,1},{0,0,-1},{-1,0,0},{1,0,0}};//上下前后左右
    static vec3 PlantNormal[]{ {-1,0,1},{1,0,1},{1,0,-1},{-1,0,-1}};//
    static vec2 UVOffset[]{vec2{0,1}*PAD,vec2{1,1}*PAD,vec2{1,0}*PAD,vec2{0,0}*PAD};
    static ivec<6> UVToFace[]{{2,3,1,0,4,5},{3,2,1,0,4,5},{0,1,2,3,4,5},{0,1,3,2,5,4},{0,1,5,4,2,3},{0,1,4,5,3,2} };
    auto GetUV=[](const ivec2*texture_indices){
        static vec2 res[6];
        for (int i = 0; i < 6; ++i)
        {
            res[i] = vec2(texture_indices[i].x, texture_indices[i].y) * PAD;
        }
        return res;
    };
    /////////////////////////////////////
    auto MakePlants=[&](Face&face,const  ivec4&point_index,int normal_index,vec2&uv){
        for(int i=0;i<4;++i)
        {
            auto&point=face.vertex[i];
            point.position=PointOffset[point_index.get(i)];
            point.normal=PlantNormal[normal_index];
            point.uv = uv + UVOffset[i];
        }
    };
    auto MakeBlocks=[&](Face&face,const ivec4&point_index,int normal_index,vec2&uv)
    {
        for(int i=0;i<4;++i)
        {
            auto&point=face.vertex[i];
            point.position=PointOffset[point_index.get(i)];
            point.normal=Normal[normal_index];
            point.uv=uv+UVOffset[i];
        }
    };
    /////////////////////////////////////
    for(int i=0;i<ITEM_NUMS;++i)
    {
        vec2*uv=GetUV(ITEM_UV[i]);
        auto&cube=BLOCK_CUBE[i];
        if(is_NotBlock(i))
        {
            ///////////////////////////////////////////
            MakePlants(cube[0][0],{0,2,6,4},0,uv[0]);
            MakePlants(cube[0][1],{3,1,5,7},1,uv[0]);
            MakePlants(cube[0][2],{2,0,4,6 },2,uv[0]);
            MakePlants(cube[0][3],{1,3,7,5 },3,uv[0]);
            /////////////////////////////////////////////
        }
        else{
            ///////////////////////////////////////////
            static ivec4 FacePoint[]{{0,1,2,3},{7,6,5,4},{3,2,6,7},{1,0,4,5},{0,3,7,4},{2,1,5,6}};
            for (int i = 0; i < 6; ++i) {
                auto& UVToFace_ = UVToFace[i];
                for (int ii = 0; ii < 6; ++ii)
                {
                    MakeBlocks(cube[i][ii],FacePoint[ii],ii,uv[UVToFace_[ii]]);
                }
            }
            ///////////////////////////////////////////
        }
    }
    ////////////////////////////////////
}

void InitRole()
{
    constexpr float minus = std::numeric_limits<float>::epsilon();
    //////////////////////设置人物速度
    camera.movespeed = RoleMoveSpeed;
    ///////////////////////初始化人物的位置
    int search =10;
    for (int x = 0; x <= search*2; ++x)
    {
        for (int z =0; z <= search*2; ++z)
        {
            auto* chunk = world->getChunk(ivec2{ x/2*(x%2?-1:1),z/2*(z%2?-1:1)}*SECTION_SIZE);
            if (chunk->TerrainHeight[0][0] > WATER_ALTITUDE)
            {
                auto& height = chunk->TerrainHeight[0][0];
                auto& pos = chunk->position;
                camera.position = vec3(pos.x+0.5,height+ 1 + RoleBox.h + minus,pos.y+0.5);
                return;
            }
        }
    }
}

void InitCloud()
{
    GenerateCloud();
}

void InitCloudRenderProgram()
{
    CloudRenderProgram=new Program("Src/Shader/Cloud/CloudRender.vert", "Src/Shader/Cloud/CloudRender.frag");
}

void InitWaterRenderProgram()
{
    WaterRenderProgram=new Program("Src/Shader/WaterRender/WaterRender.vert", "Src/Shader/WaterRender/WaterRender.frag");
    WaterRenderProgram->setuniformblock("VP", CAMERA_UBO_BINDING);
}

void InitGBuffer()
{
    GBufferProgram = new Program("Src/Shader/GBuffer/GBuffer.vert","Src/Shader/GBuffer/GBuffer.frag");
    //////////////////////////////////////////
     /////////////////////初始化GBuffer
    auto hwd = ::GetDesktopWindow();
    auto hdc = ::GetDC(hwd);
    vector<GLenum>GBufferType{GL_RGBA16F,GL_RGBA32F,GL_RGBA16F };//颜色 位置-深度 法线
    GBuffer = new DeferredRendering(GetDeviceCaps(hdc, DESKTOPHORZRES), GetDeviceCaps(hdc, DESKTOPVERTRES), GBufferType);
    //////////////////////////////////////////
}
