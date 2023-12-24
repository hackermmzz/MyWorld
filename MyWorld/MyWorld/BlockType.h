#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H
#include"Include/vec.hpp"
#include"Include/texture2d.h"
struct FaceVertex{
    vec3 position;
    vec3 normal;
    vec2 uv;
};
struct Face{
    FaceVertex vertex[4];
};
/////////////////////////////////////////////所有的block类型
#define EMPTY 0
#define GRASS 1
#define SAND 2
#define STONE 3
#define BRICK 4
#define WOOD 5
#define CEMENT 6
#define DIRT 7
#define PLANK 8
#define SNOW 9
#define GLASS 10
#define COBBLE 11
#define LIGHT_STONE 12
#define DARK_STONE 13
#define CHEST 14
#define LEAVES 15
#define CLOUD 16
#define TALL_GRASS 17
#define YELLOW_FLOWER 18
#define RED_FLOWER 19
#define PURPLE_FLOWER 20
#define SUN_FLOWER 21
#define WHITE_FLOWER 22
#define BLUE_FLOWER 23
#define BED_ROCK 24
#define WATER 25
#define MUSHROOM 26
#define PUMPKIN 27
#define CACTI 28
#define DRIED_GRASS 29
#define WHITE_BARK_TREE_WOOD 30 
#define WHITE_BARK_TREE_LEAVES 31
#define CLOVER 32
#define SEAWEED_L0 33
#define SEAWEED_L1 34
#define SEAWEED_L2 35
#define SEAWEED_L3 36
#define SEAWEED_L4 37
#define SEAWEED_L5 38
#define SEAWEED_L6 39
#define SEAWEED_L7 40
#define TNT 41
#define WORKSPACE 42
#define TORCH 43
#define LIGHTSTONE 44
///////////////////////////////////////////////
using BYTE=unsigned char;
struct  Block
{
    BYTE id;
    BYTE meta;
};
/////////////////////////////////////////////
template<class T>struct ArrayLength;
template<class T,unsigned int N>struct ArrayLength<T[N]>
{
    const static unsigned int value=N;
};
////////////////////////////////////////////////
extern vec2 FaceNumsPerAxis;//x与y轴上子纹理的个数
using CUBE=Face[6];
extern  ivec2 ITEM_UV[][6];//block类型对应的纹理索引
extern  CUBE BLOCK_CUBE[256][6];//block类型所对应的Face
extern  const int ITEM_NUMS;//block总数
extern Texture2D *BLOCK_TEXTURE;//block的基本方块纹理集
bool is_NotBlock(int type);
bool is_obstacle(int type);
bool is_obstacle(const Block& block);
bool is_transparent(int type);
bool is_destructable(int type);
bool is_functionalBlock(int type);
bool is_Distinguish_Front(int type);
bool is_Plantable(int type);
bool is_Lightable(int type);
#endif // BLOCKTYPE_H
