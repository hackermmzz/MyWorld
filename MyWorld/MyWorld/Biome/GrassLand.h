#pragma once
#include"BiomeBase.h"
struct GrassLand :BiomeBase {
	// ͨ�� BiomeBase �̳�
	GrassLand(int seed);
	// ͨ�� BiomeBase �̳�
	int GetTree() override;

	Block GetPlant() override;

	int GetSurface() override;

	int GetBeach() override;


	// ͨ�� BiomeBase �̳�
	int GetBeneath() override;

};