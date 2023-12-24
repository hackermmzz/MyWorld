#ifndef CHUNK_H
#define CHUNK_H
#include"globalsource.h"
#include"section.h"
struct Chunk
{
    BiomeType BiomeId;
    ivec2 position;
    Section* section[CHUNK_SIZE];
    int TerrainHeight[SECTION_SIZE][SECTION_SIZE];//高度图
    Block Block[SECTION_SIZE][SECTION_SIZE*CHUNK_SIZE][SECTION_SIZE];//存储实体block
    /////////////////////////////
    bool IsChunkGenerateComplete;
    bool IsBlockGenerateComplete;
    bool IsDecorationGenerateComplete;
    bool IsLoadChunk;
    bool IsLoadBlock;
    bool IsLoadDecoration;
    atomic<int> IsUsing;
    /////////////////////////////
    Chunk();
    void Init(const ivec2& pos);
    void ResetState();
    void UpdateSectionPosition();
    ~Chunk();
};

#endif // CHUNK_H
