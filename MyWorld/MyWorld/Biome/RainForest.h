#pragma once
#include"BiomeBase.h"
struct RainForest :BiomeBase
{
	RainForest(int seed);
	// 通过 BiomeBase 继承
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeach() override;

	// 通过 BiomeBase 继承
	int GetBeneath() override;
};