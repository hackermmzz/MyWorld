#include "GrassLand.h"

GrassLand::GrassLand(int seed)
    :BiomeBase(seed,WATER_ALTITUDE+40,WATER_ALTITUDE-5)
{
}

int GrassLand::GetTree()
{
    static int Treefreq = 200;
    if (rand.rand(0, Treefreq) == 0)
        return WOOD;
    return 0;
}

Block GrassLand::GetPlant()
{
    static int plantFreq = 100;
    if (rand.rand(0, plantFreq) == 0)
    {
        return rand.rand(0, 2) ? Block{SUN_FLOWER} : Block{TALL_GRASS};
    }
    return { 0 };
}

int GrassLand::GetSurface()
{
    static int grassBlockFreq = 10;
    if (rand.rand(0, grassBlockFreq))
    {
        return GRASS;
    }
    return DIRT;
}

int GrassLand::GetBeach()
{
    static int sandFreq = 10;
    if (rand.rand(0, sandFreq))return SAND;
    return rand.rand(0, 2) ? DIRT : GRASS;
}

int GrassLand::GetBeneath()
{
    return DIRT;
}
