#pragma once 
#include"BiomeBase.h"
struct ForestLand :BiomeBase
{
	ForestLand(int seed);
	// Í¨¹ý BiomeBase ¼Ì³Ð
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeneath() override;
	int GetBeach() override;
	virtual void MakeTree(int type, int x, int y, int z);
};