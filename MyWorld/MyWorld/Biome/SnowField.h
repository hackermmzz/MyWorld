#pragma once
#include"BiomeBase.h"
struct SnowFieldLand :BiomeBase {
	SnowFieldLand(int seed);
	// ͨ�� BiomeBase �̳�
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeneath() override;
	int GetBeach() override;
	void MakeTree(int type,int x, int y, int z);
};