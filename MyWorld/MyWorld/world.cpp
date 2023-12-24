#include "world.h"
////////////////////////////////
World*world;
World::World()
{
    threadpool=new ThreadPool(THREAD_POOL_NUMS);
    ////////////////////////////初始化chunk
    int HALF_CHUNK_LOAD_SIZE=CHUNK_LOAD_SIZE/2;
    for(int i=-HALF_CHUNK_LOAD_SIZE;i<=HALF_CHUNK_LOAD_SIZE;++i)
    {
        for(int ii=-HALF_CHUNK_LOAD_SIZE;ii<=HALF_CHUNK_LOAD_SIZE;++ii)
        {
            Chunk*chunk=new Chunk;
            auto position=ivec2{i*SECTION_SIZE,ii*SECTION_SIZE}+camera_chunk;
            chunk->Init(position);
            LoadChunk(chunk);
        }
    }
    /////////////////////////////添加备用chunk
    int size = CHUNK_LOAD_SIZE * 2 - 1;
    ivec2 position = { INT_MAX,INT_MAX };
    for (int i = 0; i < size; ++i)
    {
        Chunk*chunk = new Chunk();
        chunk->Init(position);
        RemovedChunk.push_back(chunk);
    }
}

Chunk *World::getChunk(const ivec2 &position, bool MapPosToChunk)
{
    static int shift = Get_2_N_POW(SECTION_SIZE);
    if (MapPosToChunk)
    {
        ivec2 temp = ivec2(position.x>>shift<<shift, position.y >> shift<< shift);
        auto itr = chunks.find(temp);
        if (itr != chunks.end())return itr->second;
        return 0;
    }
    auto itr=chunks.find(position);
    if(itr!=chunks.end())return itr->second;
    return 0;
}

Section*World::getSection(const ivec2 &position,int id)
{
    Chunk*chunk=getChunk(position);
    if(chunk)
        return chunk->section[id];
    return 0;
}

Section* World::getSection(const ivec3& position)
{
    static int shift = Get_2_N_POW(SECTION_SIZE);
    return getSection({ position.x,position.z },position.y>>shift);
}

bool World::IsBlock(int x, int y, int z)
{
    static int shift = Get_2_N_POW(SECTION_SIZE);
    static int mask = SECTION_SIZE - 1;
    static int MAX_HEIGHT = SECTION_SIZE * CHUNK_SIZE - 1;
    if (y<0||y>MAX_HEIGHT)return 0;
    Chunk* chunk = getChunk(ivec2{ x >> shift << shift,z >> shift << shift });
    return chunk->Block[x&mask][y][z&mask].id;
}

Block& World::GetBlock(int x, int y, int z)
{
    static int shift = Get_2_N_POW(SECTION_SIZE);
    static int mask = SECTION_SIZE - 1;
    Chunk* chunk = getChunk(ivec2{ x >> shift << shift,z >> shift<<shift });
    return chunk->Block[x&mask][y][z&mask];
}

void World::SetBlock(int x, int y, int z, BYTE id, BYTE meta)
{
    static int MAX_HEIGHT = CHUNK_SIZE*SECTION_SIZE - 1;
    static int shift = Get_2_N_POW(SECTION_SIZE);
    static int mask = SECTION_SIZE - 1;
    if (y > MAX_HEIGHT||y<0)return;
    Chunk* chunk = getChunk(ivec2{ x>>shift<< shift,z >>shift<<shift});
    if (chunk == 0)return;
    auto&block=chunk->Block[x&mask][y][z&mask];
    block.id = id;
    block.meta = meta;
}

void World::RemoveExtraChunks()
{
    static int remove_offset=CHUNK_LOAD_SIZE*SECTION_SIZE/2;
    using ITR_TYPE = decltype(chunks.begin());
    vector<ITR_TYPE> NeedBeRemoved;
    for(auto itr=chunks.begin();itr!=chunks.end();++itr)
    {
        auto&chunk = itr->second;
        auto offset=chunk->position-camera_chunk;
        if(chunk->IsUsing==0&&(abs(offset.x)>remove_offset||abs(offset.y)>remove_offset))
        {  
            NeedBeRemoved.push_back(itr);
        }
    }
    for (auto& remove : NeedBeRemoved)
    {
        RemovedChunk.push_back(remove->second);
       chunks.erase(remove);
    }
}

void World::LoadChunk(Chunk *chunk)
{
    chunks.insert({chunk->position,chunk});
}

World::~World()
{
    for(auto itr=chunks.begin();itr!=chunks.end();++itr)
        delete itr->second;
    for (auto itr = RemovedChunk.begin(); itr != RemovedChunk.end(); ++itr)
       delete *itr;
    if(threadpool)delete threadpool;
}

