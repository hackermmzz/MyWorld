#include "SnowField.h"

SnowFieldLand::SnowFieldLand(int seed)
    :BiomeBase(seed,WATER_ALTITUDE+60,WATER_ALTITUDE-5)
{
}

int SnowFieldLand::GetTree()
{
    static int treeFreq = 200;
    if (rand.rand(0, treeFreq) == 0)return WHITE_BARK_TREE_WOOD;
    return 0;
}

Block SnowFieldLand::GetPlant()
{
    static int plantFreq = 100;
    if (rand.rand(0, plantFreq) == 0)
    {
        int val = rand.rand(0, 10);
        if (val >= 2)return { CLOVER };
        return { DRIED_GRASS };
    }
    return { 0 };
}

int SnowFieldLand::GetSurface()
{
    static int snowFreq = 100;
    int val = rand.rand(0, snowFreq );
    if (val == 0)return DIRT;
    else if (val == 1)return SAND;
    return SNOW;
}

int SnowFieldLand::GetBeneath()
{
    return DIRT;
}

int SnowFieldLand::GetBeach()
{
    static int sandFreq = 10;
    if (rand.rand(0, sandFreq) == 0)return SAND;
    return SNOW;
}

void SnowFieldLand::MakeTree(int type, int x, int y, int z)
{
    static int treeMaxHeight = 6;
    static int treeMinHeight = 4;
    int height = rand.rand(treeMinHeight, treeMaxHeight + 1);
    //生成主干
    for (int i = 0; i < height; ++i)
    {
        world->SetBlock(x, y + i, z, WHITE_BARK_TREE_WOOD, 2);
    }
    //生成树叶
    static int leavesMinWidth = 1;
    static int leavesMaxWidth = 3;
    int leavesWidth = rand.rand(leavesMinWidth, leavesMaxWidth + 1);
    int leavesHeight = rand.rand(1, 4);
    float fac = (-leavesWidth * 1.0 / leavesHeight / leavesHeight);
    for (int i = 0; i < leavesHeight; ++i) {
        int width = fac * (i + leavesHeight) * (i - leavesHeight);
        for (int ii = -width; ii <= width; ++ii) {
            for (int iii = -width; iii <= width; ++iii)
            {

                world->SetBlock(x + ii, y + height - 1 + i, z + iii, WHITE_BARK_TREE_LEAVES,2);
                world->SetBlock(x + ii, y + height - 1 - i, z + iii, WHITE_BARK_TREE_LEAVES,2);
            }
        }
    }
}

