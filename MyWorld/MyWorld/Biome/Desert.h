#pragma once
#include"BiomeBase.h"
struct DesertLand :BiomeBase {
	DesertLand(int seed);
	// ͨ�� BiomeBase �̳�
	int GetTree() override;
	Block GetPlant() override;
	int GetSurface() override;
	int GetBeneath() override;
	int GetBeach() override;
	virtual void MakeTree(int type, int x, int y, int z);
};