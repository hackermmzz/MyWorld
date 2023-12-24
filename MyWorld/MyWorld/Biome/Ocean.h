#pragma once
#include"BiomeBase.h"
struct OceanLand :BiomeBase {
	OceanLand(int seed);

	// Í¨¹ý BiomeBase ¼Ì³Ð
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeneath() override;
	int GetBeach() override;
};