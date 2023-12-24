#pragma once
#include"BiomeBase.h"
struct PlainLand :BiomeBase {
	// 通过 BiomeBase 继承
	PlainLand(int seed);
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeach() override;

	// 通过 BiomeBase 继承
	int GetBeneath() override;
};