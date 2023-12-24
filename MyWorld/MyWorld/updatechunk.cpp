#include "updatechunk.h"
void UpdateChunk(const ivec2&position)
{ 
    /////////////////////////////先在removedchunk里面找
    auto& removedChunks=world->RemovedChunk;
    auto itr = find_if(removedChunks.begin(), removedChunks.end(), [&](Chunk* chunk) {
        return chunk->position.equal(position);
        });
    if (itr != removedChunks.end())
    {
        removedChunks.erase(itr);
        world->LoadChunk(*itr);
        return;
    }
    /////////////////////////////否则就在子线程加载
    Chunk* chunk;
    if (removedChunks.size())
    {
        chunk = removedChunks.front();
        removedChunks.pop_front();
    }
    else chunk = new Chunk();
    ////////////////////////////
    chunk->Init(position);
    world->LoadChunk(chunk);
    ////////////////////////////
    chunk->IsLoadChunk = 1;
    chunk->IsLoadBlock = 1;
    chunk->IsUsing++;
    threadPool->append([=](){
        GenerateTerrain(chunk);
        GenerateBlock(chunk);
        chunk->IsUsing--;
    });
}

void UpdateAllChunks()
{
    static int half_chunk_load_size=CHUNK_LOAD_SIZE/2;
    static int half_chunk_render_size = CHUNK_RENDER_SIZE / 2;
    ////////////////////////////////////////////加载所有没有加载的区块
    for (int x = -half_chunk_load_size; x <= half_chunk_load_size; ++x)
    {
        for (int z = -half_chunk_load_size; z <= half_chunk_load_size; ++z)
        {
            ivec2 position = ivec2{ x,z }*SECTION_SIZE + camera_chunk;
            auto* chunk = world->getChunk(position);
            if (!chunk) {
                UpdateChunk(position);
            }
        }
    }
    /////////////////////////////////////////////加载装饰和面
    for (int x = -half_chunk_render_size; x <= half_chunk_render_size; ++x)
    {
        for (int z = -half_chunk_render_size; z <= half_chunk_render_size; ++z)
        {
            ivec2 pos = ivec2{ x,z }*SECTION_SIZE+camera_chunk;
            auto* chunk = world->getChunk(pos);
            ///////////////////////////
            if (chunk->IsBlockGenerateComplete==0)continue;
            if (chunk->IsLoadDecoration==1&&chunk->section[10]->IsLoadFace == 1)continue;
            auto cnc = GetChunkNearChunks(chunk);
            if (!cnc.CheckAll())continue;
            //////////////////////////产生装饰
            if (chunk->IsLoadDecoration == 0)
            {
                ////////////////////////////如果四周的区块未产生则直接返回
                if (!cnc.left->IsBlockGenerateComplete ||!cnc.right->IsBlockGenerateComplete
                    || !cnc.front->IsBlockGenerateComplete || !cnc.back->IsBlockGenerateComplete
                    )continue;
                /////////////////////////////////////////
                chunk->IsLoadDecoration =1;
                cnc.UseAll();
                threadPool->append([=]() {
                    GenerateDecoration(chunk);
                    auto cnc_ = cnc;
                    cnc_.DisUseAll();
                    });
                continue;
            }
            //////////////////////////////////////////产生面
          if (chunk->section[0]->IsLoadFace == 0) {
                if (!cnc.left->IsDecorationGenerateComplete||!cnc.right->IsDecorationGenerateComplete || !cnc.front->IsDecorationGenerateComplete
               ||!cnc.back->IsDecorationGenerateComplete)
                    continue;
                ///////////////////////////////////////
                cnc.UseAll();
                for (auto& section : chunk->section)
                    section->IsLoadFace = 1;
                  threadPool->append([=]() {
                      for (auto& section : chunk->section)
                      {
                          GenerateFace(section, cnc);
                      }
                    auto cnc_ = cnc;
                    cnc_.DisUseAll(); 
                    });
            }
        }
    }
}
