#include "generateface.h"
#include "globalsource.h"
void GenerateFace(Section*section,const ChunkNearChunks&cnc)
{   /////////////////////////////////////////////
    static int MAX_HEIGHT = CHUNK_SIZE * SECTION_SIZE - 1;
    auto* chunk = (Chunk*)(section->Chunk);
    /////////////////////////////////////////////检测当前区块的植物等是否生成
    //////////////////////////////////////////////
    auto& left_block=cnc.left->Block;
    auto& right_block=cnc.right->Block;
    auto& front_block =cnc.front->Block;
    auto& back_block =cnc.back->Block;
    ////////////////////////////////////////////
    auto& blocks = chunk->Block;
    auto& height_map= chunk->TerrainHeight;
    auto sectionPos = section->position;
    int height_end = sectionPos.y + SECTION_SIZE;
    auto& buffer = section->face;
    buffer.clear();
    auto& waterbuffer = section->waterFace;
    waterbuffer.clear();
    for(int x=0;x<SECTION_SIZE;++x)
    {
        for(int z=0;z<SECTION_SIZE;++z)
        {
            for(int y=sectionPos.y;y<height_end;++y)
            {
                vec3 position = vec3(x + sectionPos.x, y, z +sectionPos.z);
                auto& block = blocks[x][y][z];
                if (!block.id) continue;
                ///////////////////////////////////////////////////////如果是植物
                if (is_NotBlock(block.id)) {
                    MakePlantFace(section, block, position);
                    continue;
                }
                ///否则就按方块处理
                //////////////////////////////////////////////////轮询立方体6个面
                ///上
                 if(
                     y+1>MAX_HEIGHT||JudgeVisible(blocks,x,y+1,z))MakeBlockFace(section,block,position,0);
                //下
                if(y-1<0||JudgeVisible(blocks,x, y - 1, z))MakeBlockFace(section,block,position,1);
                //前
                if (z + 1 == SECTION_SIZE)
                {
                    if (JudgeVisible(front_block, x, y, 0))MakeBlockFace(section,block,position,2);
                }
                else if(JudgeVisible(blocks, x,y,z+1))MakeBlockFace(section,block, position,2);
               //后
                if (z == 0)
                {
                    if (JudgeVisible(back_block, x, y, SECTION_SIZE - 1))MakeBlockFace(section,block, position,3);
                }
                else if(JudgeVisible(blocks, x, y,z-1))MakeBlockFace(section,block, position,3);
                //左
                if (x == 0)
                {
                    if (JudgeVisible(left_block, SECTION_SIZE - 1, y, z))MakeBlockFace(section,block, position,4);
                }
                else if(JudgeVisible(blocks,x-1, y, z))MakeBlockFace(section,block, position,4);
                //右
                if (x + 1 == SECTION_SIZE)
                {
                    if (JudgeVisible(right_block, 0, y, z))MakeBlockFace(section,block, position,5);
                }
                else if(JudgeVisible(blocks, x+1, y,z))MakeBlockFace(section,block, position,5);
            }
        }
    }
    section->IsFaceGenerateComplete=1;
}

void MakeBlockFace(Section* section,Block& block, vec3&position, int dir)
{
 thread_local static Face face;
 if (block.id == WATER)
 {
     /////只生成最顶面
     if (!(position.y == WATER_ALTITUDE && dir == 0))return;
     static float minus_y = 0.1;
         face = BLOCK_CUBE[BED_ROCK][2][dir];
         for (auto& vertex : face.vertex)vertex.position.y -=minus_y;
         face.vertex[0].uv = vec2(0, 1);
         face.vertex[1].uv = vec2(1, 1);
         face.vertex[2].uv = vec2(1, 0);
         face.vertex[3].uv = vec2(0, 0);
 }
 else
 {
     face =BLOCK_CUBE[block.id][block.meta][dir];
 }
 for (int i = 0; i < 4; ++i)
     face.vertex[i].position += position;
if (block.id == WATER) section->waterFace.emplace_back(face);
else section->face.emplace_back(face);
}

void MakePlantFace(Section* section, Block& block, vec3& position)
{
    static thread_local Face face;
    for (int i = 0; i < 4; ++i)
    {
        face = BLOCK_CUBE[block.id][0][i];
        for (int ii = 0; ii < 4; ++ii)
        {
            face.vertex[ii].position += position;
        }
        section->face.emplace_back(face);
    }
}

bool JudgeVisible(Block block[SECTION_SIZE][SECTION_SIZE * CHUNK_SIZE][SECTION_SIZE], int x, int y, int z)
{
    auto&id=block[x][y][z].id;
    return !id||id == WATER||is_NotBlock(id);
}

ChunkNearChunks GetChunkNearChunks(Chunk* chunk)
{
    auto& pos = chunk->position;
    auto* left_chunk = world->getChunk(pos - ivec2{ SECTION_SIZE,0 });
    auto* right_chunk = world->getChunk(pos + ivec2{ SECTION_SIZE,0 });
    auto* front_chunk = world->getChunk(pos + ivec2{ 0,SECTION_SIZE });
    auto* back_chunk = world->getChunk(pos - ivec2{ 0,SECTION_SIZE });
    return { front_chunk,back_chunk,left_chunk,right_chunk };
}

void ChunkNearChunks::UseAll()
{
    left->IsUsing++;
    right->IsUsing++;
    front->IsUsing++;
    back->IsUsing++;
}

void ChunkNearChunks::DisUseAll()
{
    left->IsUsing--;
    right->IsUsing--;
    front->IsUsing--;
    back->IsUsing--;
}

bool ChunkNearChunks::CheckAll()
{
    return (left && right && front && back);
}
