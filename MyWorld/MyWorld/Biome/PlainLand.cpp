#include "PlainLand.h"

PlainLand::PlainLand(int seed)
	:BiomeBase(seed,WATER_ALTITUDE+5,WATER_ALTITUDE-5)
{
}

int PlainLand::GetTree()
{
	return 0;
}

Block PlainLand::GetPlant()
{
	static int plantFreq = 100;
	if (rand.rand(0, plantFreq) == 0)
	{
		int val = rand.rand(0, 100);
		if (val >= 70)return { TALL_GRASS };
		else if (val >= 50)return { SUN_FLOWER };
		else return { MUSHROOM };
	}
	return {0};
}

int PlainLand::GetSurface()
{
	return GRASS;
}

int PlainLand::GetBeach()
{
	static int sandFreq = 10;
	if (rand.rand(0, sandFreq))return SAND;
	return GRASS;
}

int PlainLand::GetBeneath()
{
	return DIRT;
}
