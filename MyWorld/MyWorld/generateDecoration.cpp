#include "generateDecoration.h"
void GenerateDecoration(Chunk* chunk)
{
	///////////////////////////////
	auto& heightMap = chunk->TerrainHeight;
	auto& pos = chunk->position;
	auto& block = chunk->Block;
	BiomeBase* biomeGenerator = GetBiomeGenerator(chunk);
	thread_local static  OceanLand oceanBiomeGenerator(0);//如果低于水平线使用这个生成器
	oceanBiomeGenerator.rand.SetSeed(pos.x * pos.y + pos.x + pos.y);
	for (int x = 0; x < SECTION_SIZE; ++x)
	{
		for (int z = 0; z < SECTION_SIZE; ++z)
		{
			int height = heightMap[x][z];
			auto blockType = chunk->Block[x][height][z].id;
			//////////////////////////////判断是否可以种植植物
			if (!is_Plantable(blockType))continue;
			//////////////////////////////
			int y = height + 1;
			Block decoration;
			if (height < WATER_ALTITUDE)
			{
				if (height == WATER_ALTITUDE-1)continue;
				decoration = oceanBiomeGenerator.GetPlant();
				if(decoration.id)
				{
					oceanBiomeGenerator.MakePlant(decoration,x+pos.x,y,z+pos.y);
				}
			}
			else {
				///////////////////////产生沙滩
				if (height==WATER_ALTITUDE)
				{
					decoration.id =biomeGenerator->GetBeach();
					decoration.meta = 2;
					auto pos_ =ivec3(x+pos.x,height,z+pos.y);
					if (decoration.id!= world->GetBlock(pos_.x, pos_.y, pos_.z).id) {
						if (world->GetBlock(pos_.x + 1, pos_.y, pos_.z).id == WATER ||
							world->GetBlock(pos_.x - 1, pos_.y, pos_.z).id == WATER ||
							world->GetBlock(pos_.x, pos_.y, pos_.z - 1).id == WATER ||
							world->GetBlock(pos_.x, pos_.y, pos_.z + 1).id == WATER
							)
							block[x][height][z].id = decoration.id;
					}
				}
				///////////////////////产生tree
				if (decoration.id = biomeGenerator->GetTree())
				{
					biomeGenerator->MakeTree(decoration.id, x + pos.x, y, z + pos.y);
					continue;
				}
				decoration = biomeGenerator->GetPlant();
				if (decoration.id)
				{
					biomeGenerator->MakePlant(decoration, x + pos.x, y, z + pos.y);
				}
			}
		}
	}
	//////////////////////////////////////////
	delete biomeGenerator;
	/////////////////////////////////////////
	chunk->IsDecorationGenerateComplete = 1;
}
