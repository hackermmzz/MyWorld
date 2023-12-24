#ifndef GENERATEBLOCK_H
#define GENERATEBLOCK_H
#include"globalsource.h"
#include"world.h"
#include"section.h"
#include"Biome/Header.h"
void GenerateBlock(Chunk*chunk);
void GenerateCave(Chunk* chunk);
BiomeBase* GetBiomeGenerator(Chunk*chunk);
#endif // GENERATEBLOCK_H
