#include "RainForest.h"

RainForest::RainForest(int seed)
    :BiomeBase(seed,WATER_ALTITUDE+70,WATER_ALTITUDE-10)
{
}

int RainForest::GetTree()
{
    static int treeFreq = 100;
    if (rand.rand(0, treeFreq)==0)return WOOD;
    return 0;
}

Block RainForest::GetPlant()
{
    static int plantFreq =50;
    if (rand.rand(0, plantFreq)==0)
    {
        int val = rand.rand(0,100);
        if (val >= 80)return { SUN_FLOWER };
        else if (val >= 60)return { PUMPKIN,(BYTE)rand.rand(2,6)};
        else if (val >= 30)return { MUSHROOM };
        else return { TALL_GRASS };
    }
    return { 0 };
}

int RainForest::GetSurface()
{
    return GRASS;
}

int RainForest::GetBeach()
{
    static int sandFreq = 100;
    if (rand.rand(0, sandFreq) == 0)return SAND;
    return GRASS;
}

int RainForest::GetBeneath()
{
    return DIRT;
}
