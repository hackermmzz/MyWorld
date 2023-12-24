#ifndef WORLD_H
#define WORLD_H
#include"chunk.h"
#include<map>
#include<list>
using std::list;
using std::map;
struct World{
map<ivec2,Chunk*>chunks;
list<Chunk*>RemovedChunk;
ThreadPool*threadpool;
World();
Chunk* getChunk(const ivec2& position, bool MapPosToChunk=0);
Section*getSection(const ivec2&position,int id);
Section* getSection(const ivec3& position);
bool IsBlock(int x, int y,int z);
Block& GetBlock(int x, int y, int z);
void SetBlock(int x, int y, int z,BYTE id,BYTE meta);
void RemoveExtraChunks();
void LoadChunk(Chunk*chunk);
~World();
};
extern World* world;
#endif // WORLD_H
