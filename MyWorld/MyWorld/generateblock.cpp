#include "generateblock.h"
void GenerateBlock(Chunk*chunk)
{
    /////////////////////////////////
    auto& biome = chunk->BiomeId;
    auto& data = chunk->Block;
    auto& pos = chunk->position;
    static int MAX_HEIGHT = SECTION_SIZE * CHUNK_SIZE - 1;
    //////////////////////////////根据对应的生物群系获得对应的生物群系生成器
    BiomeBase* BiomeGenerator = GetBiomeGenerator(chunk);
    thread_local static  OceanLand oceanBiomeGenerator(0);//如果低于水平线使用这个生成器
    oceanBiomeGenerator.rand.SetSeed(pos.x * pos.y + pos.x + pos.y);
    //////////////////////////////
    ivec3 BlockPos;
    auto MapEnd = BlockChanged.end();
    for (int x = 0; x < SECTION_SIZE; ++x)
    {
        BlockPos.x = x + pos.x;
        for (int z = 0; z < SECTION_SIZE; ++z)
        {
            BlockPos.z = z + pos.y;
            auto& height = chunk->TerrainHeight[x][z];    
            if (height > MAX_HEIGHT)height = MAX_HEIGHT;
            for (int y = 0; y <=MAX_HEIGHT; ++y)
            {
                auto& block=data[x][y][z];
                block.meta = 2;//正面的朝向默认为2
                auto& blockID = block.id;
                ///////////////////////////////////////
                auto itr=BlockChanged.find(ivec3(BlockPos.x,y, BlockPos.z));
                if (itr != MapEnd)
                 {
                 block=itr->second;
                 continue;
                 }
                else if(y>height)
                  continue;
            ///////////////////////////////////////
                if (y <= BED_ROCK_DEPTH)//生成基岩
                    blockID = BED_ROCK;    
                else if (y == height && height >=WATER_ALTITUDE)blockID = BiomeGenerator->GetSurface();
                else if (y > height - 4)blockID = BiomeGenerator->GetBeneath();
                else 
                {
                    blockID = STONE;
                }
            }
            ////////////////////////////////////////////生成水和河床
            if (height < WATER_ALTITUDE)data[x][height][z].id = oceanBiomeGenerator.GetSurface();
            for (int y = height+1; y <= WATER_ALTITUDE; ++y)
            {
                auto& blockID = data[x][y][z].id;
                blockID = WATER;
            }
        }
    }
    //////////////////////////////////////////产生洞穴
    if (biome != OCEAN)GenerateCave(chunk);
   ///////////////////////////////////////////释放生物群系产生器
    delete BiomeGenerator;
   ////////////////////////////////////////////
    chunk->IsBlockGenerateComplete=1;
}

void GenerateCave(Chunk* chunk)
{
    thread_local static PerlinNoise CaveGenerator;
    static float NOISE_DIV = SECTION_SIZE * 2;
    auto& heights = chunk->TerrainHeight;
    auto& data = chunk->Block;
    auto& pos = chunk->position;
    for (int x = 0; x < SECTION_SIZE; ++x)
    {
        float xx = (x+pos.x) / NOISE_DIV;
        for (int z = 0; z < SECTION_SIZE; ++z)
        {
            auto& height = heights[x][z];
            auto height_ = height;
            float zz = (z+pos.y) / NOISE_DIV;
            for (int y = height_; y > BED_ROCK_DEPTH; --y)
            {
                float val=y*0.8f/height_+CaveGenerator.noise3D(xx,y/NOISE_DIV,zz);
                if (val < 0)
                {
                    if (y == height)height--;
                   data[x][y][z].id = 0;
                }
            }
        }
    }
}

BiomeBase* GetBiomeGenerator(Chunk* chunk)
{
    auto& biome = chunk->BiomeId;
    auto& pos = chunk->position;
    int seed = pos.x * pos.y + pos.x + pos.y;
    if (biome == GRASSLAND)return new GrassLand(seed);
    else if (biome == PLAIN)return new PlainLand(seed);
    else if (biome == RAINFOREST)return new RainForest(seed);
    else if (biome == DESERT)return new DesertLand(seed);
    else if (biome == FOREST)return new ForestLand(seed);
    else if (biome == SNOWFIELD)return new SnowFieldLand(seed);
    else if (biome == OCEAN)return new OceanLand(seed);
    return 0;
}
