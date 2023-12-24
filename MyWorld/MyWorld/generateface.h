#ifndef GENERATEFACE_H
#define GENERATEFACE_H
#include"globalsource.h"
#include"world.h"
#include"section.h"
#include"generateterrain.h"
/////////////////////////////////////
struct ChunkNearChunks
{
	Chunk* front;
	Chunk* back;
	Chunk* left;
	Chunk* right;
	void UseAll();
	void DisUseAll();
	bool CheckAll();
};
////////////////////////////////////
void GenerateFace(Section* section,const ChunkNearChunks&cnc);
void MakeBlockFace(Section*section,Block& block,vec3&position,int dir);
void MakePlantFace(Section* section, Block& block, vec3& position);
bool JudgeVisible(Block block[SECTION_SIZE][SECTION_SIZE * CHUNK_SIZE][SECTION_SIZE],int x, int y,int z);
ChunkNearChunks GetChunkNearChunks(Chunk*chunk);
#endif // GENERATEFACE_H
