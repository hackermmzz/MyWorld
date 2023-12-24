#include "Forest.h"

ForestLand::ForestLand(int seed)
    :BiomeBase(seed,WATER_ALTITUDE+100,WATER_ALTITUDE-4)
{
}

int ForestLand::GetTree()
{
    static int treeFreq = 100;
    if (rand.rand(0, treeFreq) == 0)
    {
        return rand.rand(0, 2) ? WOOD : WHITE_BARK_TREE_WOOD;
    }
    return 0;
}

Block ForestLand::GetPlant()
{
    static int plantFreq = 50;
    if (rand.rand(0, plantFreq) == 0)
    {
        int val = rand.rand(0, 100);
        if (val >= 80)return { SUN_FLOWER };
        else if (val >= 60)return { PUMPKIN,(BYTE)rand.rand(2,6)};
        else if (val >= 30)return { MUSHROOM };
        else return { TALL_GRASS };
    }
    return { 0 };
}

int ForestLand::GetSurface()
{
    return GRASS;
}

int ForestLand::GetBeneath()
{
    return DIRT;
}

int ForestLand::GetBeach()
{
    static int sandFreq = 100;
    int val = rand.rand(0, sandFreq);
    if (val >= 80)return DIRT;
    else if (val >= 1)return GRASS;
    return SAND;
}

void ForestLand::MakeTree(int type, int x, int y, int z)
{
    static int treeMinHeight = 5;
    static int treeMaxHeight = 20;
    int height = rand.rand(treeMinHeight, treeMaxHeight + 1);
    for (int i = 0; i < height; ++i)
    {
        world->SetBlock(x, y + i, z, type, 2);
    }
    static int leavesMinWidth = 3;
    static int leavesMaxWidth = 4;
    auto leavesType = WHITE_BARK_TREE_WOOD ? WHITE_BARK_TREE_LEAVES : LEAVES;;
    int leavesWidth = rand.rand(leavesMinWidth, leavesMaxWidth + 1);
    int leavesHeight = rand.rand(1,4);
    ////////////////////////构建二次函数
    float fac = (-leavesWidth * 1.0 / leavesHeight / leavesHeight);
    for (int i = 0; i <leavesHeight; ++i) {
        int width = fac * (i+ leavesHeight) * (i - leavesHeight);
        for (int ii = -width; ii <= width; ++ii) {
            for (int iii = -width; iii <= width; ++iii)
            {
                world->SetBlock(x + ii, y + height - 1 + i, z + iii, leavesType, 2);
                world->SetBlock(x + ii, y + height - 1 - i, z + iii, leavesType, 2);
            }
        }
    }
}
