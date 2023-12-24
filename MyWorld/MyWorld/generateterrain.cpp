#include "generateterrain.h"
void GenerateTerrain(Chunk*chunk)
{
    ////////////////////////////////////
    thread_local static vector<TerrainConfigInfo>ContinentalLevel;
    thread_local static vector<TerrainConfigInfo>ErosionLevel;
    thread_local static vector<TerrainConfigInfo>PeakLevel;
    thread_local static bool init = 0;
    if (!init)
    {
        init = 1;
        ConfigTerrain(ContinentalLevel, ErosionLevel, PeakLevel);
    }
    ////////////////////////////////////
    auto&height=chunk->TerrainHeight;
    auto& block = chunk->Block;
    memset(block, 0, sizeof(block));
    vec2 pos=vec2(float(chunk->position.x),float(chunk->position.y));
    thread_local static float ErosionNoiseData[SECTION_SIZE][SECTION_SIZE];
    thread_local static float PeakNoiseData[SECTION_SIZE][SECTION_SIZE];
    static int FBM = 4;
    static const float minus = std::numeric_limits<float>::epsilon();
    thread_local static auto HeightLerp = [&](float source,vector<TerrainConfigInfo>&tar){
        source=fmax(source, -1.0 + minus);
        source=fmin(source, 1.0 - minus);
        TerrainConfigInfo sourceInfo = { source };
        int index=upper_bound(tar.begin(), tar.end(), sourceInfo) - tar.begin();
        auto& info1 = tar[index-1];
        auto& info2 = tar[index];
        auto weight = (source - info1.keyPointX) / (info2.keyPointX - info1.keyPointX);
        return info1.keyPointY * (1.0 - weight) + info2.keyPointY * weight;
        };
    /////////////////////////////////////////////获得生物群系
    float Continental = GenerateBiomeMap(chunk->position, chunk->BiomeId);
    float ContinentalHeight = HeightLerp(Continental, ContinentalLevel);
    /////////////////////////////////////////////生成高度图
    for (int x = 0; x < SECTION_SIZE; ++x)
    {
        for (int z = 0; z < SECTION_SIZE; ++z)
        {
            float xx = (x + pos.x), zz = (z + pos.y);
            //生成Erosion噪声
            ErosionNoiseData[x][z]=ErosionNoise.octave2D_11(xx/EROSIONNOISEFREQ, zz/EROSIONNOISEFREQ, FBM);
            //生成Peak噪声
            PeakNoiseData[x][z] =PeaksNoise.octave2D_01(xx/PEAKNOISEFREQ, zz/PEAKNOISEFREQ, FBM);
        }
   }
    /////////////////////////////////////////////按权重累加各类噪声值获得高度值
    static int MAX_HEIGHT = SECTION_SIZE * CHUNK_SIZE-1;
    for (int x = 0; x < SECTION_SIZE; ++x)
    {
        for (int z = 0; z < SECTION_SIZE; ++z)
        {
            constexpr static  float factor = 1 - CONTINENALNOISE_WEIGHT;
            constexpr static float Landweight = 1 - OCEAN_WEIGHT;
            float res = ContinentalHeight * CONTINENALNOISE_WEIGHT +
                ErosionNoiseData[x][z]*3+
                PeakNoiseData[x][z]*128*Continental*factor;
            height[x][z] = res;
        }
    }
   //////////////////////////////////////////////设置完成标志
    chunk->IsChunkGenerateComplete=1;
    //
}

void ConfigTerrain(vector<TerrainConfigInfo>& Continental, vector<TerrainConfigInfo>& Erosion, vector<TerrainConfigInfo>& Peak)
{
    static int MAX_HEIGHT = CHUNK_LOAD_SIZE * SECTION_SIZE-1;
    static int TerrainMaxHeight = MAX_HEIGHT*2/3;
    static int TerrainMinHeight = WATER_ALTITUDE / 2;
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    Continental = {
    {0.0,TerrainMinHeight},{OCEAN_WEIGHT,WATER_ALTITUDE},{0.55,WATER_ALTITUDE+10},
    {0.65,WATER_ALTITUDE + 50},{0.8,WATER_ALTITUDE+80},{0.9,WATER_ALTITUDE + 140},
    {1.0,TerrainMaxHeight}
    };
    //////////////////////////////////////////
    Erosion = {
    {0.0,TerrainMaxHeight},{0.15,TerrainMaxHeight-100},
    {0.25,TerrainMaxHeight-135},{0.7,TerrainMinHeight+40},
    {1.0,TerrainMinHeight}
    };
    /////////////////////////////////////////
    Peak = { {0.0,TerrainMinHeight},{0.25,WATER_ALTITUDE},{0.5,TerrainMaxHeight * 4 / 5},{1.0,TerrainMaxHeight} };
}

