#pragma once
#include"BiomeBase.h"
struct PlainLand :BiomeBase {
	// ͨ�� BiomeBase �̳�
	PlainLand(int seed);
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeach() override;

	// ͨ�� BiomeBase �̳�
	int GetBeneath() override;
};