#ifndef UPDATECHUNK_H
#define UPDATECHUNK_H
#include"globalsource.h"
#include"generateblock.h"
#include"generateterrain.h"
#include"generateface.h"
#include"generateDecoration.h"
#include"world.h"
void UpdateAllChunks();
void UpdateChunk(const ivec2&position);
#endif // UPDATECHUNK_H
