#include "Ocean.h"

OceanLand::OceanLand(int seed)
	:BiomeBase(seed,WATER_ALTITUDE-3,WATER_ALTITUDE-50)
{
}

int OceanLand::GetTree()
{
	return 0;
}

Block OceanLand::GetPlant()
{
	static int plantFreq = 300;
	if (rand.rand(0, plantFreq) == 0)
	{
		int val = rand.rand(0, 100);
		if (val >= 90)return { SEAWEED_L7 };
		else if (val >= 70)return { SEAWEED_L6 };
		else if (val >= 60)return { SEAWEED_L5 };
		else if (val >= 50)return { SEAWEED_L4 };
		else if (val >= 40)return { SEAWEED_L3 };
		else if (val >= 30)return { SEAWEED_L2 };
		else if (val >= 20)return { SEAWEED_L1 };
		else if (val >= 10)return { SEAWEED_L0 };
		else return { MUSHROOM };
	}
	return { 0 };
}

int OceanLand::GetSurface()
{
	static int stoneFreq = 10;
	if (rand.rand(0, stoneFreq) == 0)return STONE;
	return DIRT;
}

int OceanLand::GetBeneath()
{
	static int stoneFreq = 10;
	if (rand.rand(0, stoneFreq) == 0)return STONE;
	return DIRT;
}

int OceanLand::GetBeach()
{
	return 0;
}
