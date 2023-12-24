#ifndef GENERATECHUNK_H
#define GENERATECHUNK_H
#include"globalsource.h"
#include"GenerateBiomeMap.h"
#include"chunk.h"
#include"world.h"
struct TerrainConfigInfo {
	float keyPointX;
	int keyPointY;
	friend bool operator<(const TerrainConfigInfo& i1, const TerrainConfigInfo& i2)
	{
		return i1.keyPointX < i2.keyPointX;
	}
};
void GenerateTerrain(Chunk*chunk);
void ConfigTerrain(vector<TerrainConfigInfo>& Continental, vector<TerrainConfigInfo>& Erosion, vector<TerrainConfigInfo>& Peak);
#endif // GENERATECHUNK_H
