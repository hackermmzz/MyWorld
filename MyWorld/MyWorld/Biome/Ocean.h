#pragma once
#include"BiomeBase.h"
struct OceanLand :BiomeBase {
	OceanLand(int seed);

	// ͨ�� BiomeBase �̳�
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeneath() override;
	int GetBeach() override;
};