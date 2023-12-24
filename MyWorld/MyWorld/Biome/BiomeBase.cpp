#include "BiomeBase.h"

BiomeBase::BiomeBase(int seed, int maxHeight_, int minHeight_)
{
	rand.SetSeed(seed);
	maxHeight = maxHeight_;
	minHeight = minHeight_;
}

void BiomeBase::MakeTree(int type,int x, int y, int z)
{
	static int treeMaxHeight = 10;
	static int treeMinHeight = 6;
	int height = rand.rand(treeMinHeight, treeMaxHeight + 1);
	//生成主干
	for (int i = 0; i < height; ++i)
		world->SetBlock(x, y + i,z,WOOD,2);
	//生成树叶
	static int leavesMinWidth = 2;
	static int leavesMaxWidth = 5;
	int leavesWidth = rand.rand(leavesMinWidth, leavesMaxWidth + 1);
	int leavesHeight = rand.rand(1,4);
	////////////////////////构建二次函数
	float fac = (-leavesWidth * 1.0 / leavesHeight / leavesHeight);
	for (int i = 0; i < leavesHeight; ++i) {
		int width = fac * (i + leavesHeight) * (i - leavesHeight);
		for (int ii = -width; ii <= width; ++ii) {
			for (int iii = -width; iii <= width; ++iii)
			{
				world->SetBlock(x + ii, y + height - 1 + i, z + iii, LEAVES, 2);
				world->SetBlock(x + ii, y + height - 1 - i, z + iii, LEAVES, 2);
			}
		}
	}
}

void BiomeBase::MakePlant(Block block,int x, int y, int z)
{
	world->SetBlock(x, y, z, block.id,block.meta);
}
