#pragma once
#include"BiomeBase.h"
struct RainForest :BiomeBase
{
	RainForest(int seed);
	// ͨ�� BiomeBase �̳�
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeach() override;

	// ͨ�� BiomeBase �̳�
	int GetBeneath() override;
};