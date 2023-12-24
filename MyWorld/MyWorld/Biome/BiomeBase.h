#pragma once
#include"../globalsource.h"
#include"../world.h"
struct  BiomeBase
{
	Random rand;
	int maxHeight, minHeight;
	BiomeBase(int seed,int maxHeight,int minHeight);
	virtual int GetTree()= 0;
	virtual Block GetPlant() = 0;
	virtual int GetSurface()=0;
	virtual int GetBeneath() = 0;
	virtual int GetBeach() = 0;
	virtual void MakeTree(int type,int x, int y, int z);
	virtual void MakePlant(Block block,int x, int y, int z);
};