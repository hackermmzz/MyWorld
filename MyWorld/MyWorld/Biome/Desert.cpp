#include "Desert.h"

DesertLand::DesertLand(int seed)
    :BiomeBase(seed,WATER_ALTITUDE+20,WATER_ALTITUDE+1)
{
}

int DesertLand::GetTree()
{
    static int treeFreq = 1000;
    if (rand.rand(0, treeFreq) == 0)return 1;
    return 0;
}

Block DesertLand::GetPlant()
{
    static int plantFreq = 1000;
    if (rand.rand(0, plantFreq) == 0)return {DRIED_GRASS};
    return { 0 };
}

int DesertLand::GetSurface()
{
    return SAND;
}

int DesertLand::GetBeneath()
{
    return SAND;
}

int DesertLand::GetBeach()
{
    static int sandFreq = 10;
    if (rand.rand(0, sandFreq) == 0)return SAND;
    return GRASS;
}

void DesertLand::MakeTree(int type, int x, int y, int z)
{
    static int minHeight = 4;
    static int maxHeight = 8;
    int height = rand.rand(minHeight, maxHeight + 1);
    for (int i = 0; i < height; ++i)
        world->SetBlock(x, y + i, z, CACTI, 2);
}
