#include "chunk.h"


Chunk::Chunk()
{
    ///////////////////
    /////////////////生成section
    for (auto& ele : section)
    {
        ele = new Section();
        ele->Chunk = this;
   }
}

void Chunk::Init(const ivec2& pos)
{
    position = pos;
    ResetState();
    UpdateSectionPosition();
    for (auto& ele : section)ele->ResetState();
}

void Chunk::ResetState()
{
    IsChunkGenerateComplete=0;
    IsBlockGenerateComplete = 0;
    IsDecorationGenerateComplete = 0;
    IsLoadChunk = 0;
    IsLoadBlock = 0;
    IsLoadDecoration = 0;
    IsUsing = 0;
}


void Chunk::UpdateSectionPosition()
{
    static int ChunkHeight=CHUNK_SIZE/2*SECTION_SIZE;
    static int shift = Get_2_N_POW(SECTION_SIZE);
    for(int i=0;i<CHUNK_SIZE;++i)
    {
        section[i]->position= ivec3(position.x,i<< shift,position.y);
        section[i]->id=i;
    }
}

Chunk::~Chunk()
{
    for(auto&b:section)
     if(b)delete b;
}
