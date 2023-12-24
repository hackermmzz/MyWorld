#include"BlockType.h"
CUBE BLOCK_CUBE[256][6];
ivec2 ITEM_UV[][6]
    {
    //top bottom front back left right
    {{0,1},{0,1},{0,1},{0,1},{0,1},{0,1}},//empty
    {{4,13},{2,15},{2,15},{2,15},{2,15},{2,15}},//grass
    {{2,14},{2,14},{2,14},{2,14},{2,14},{2,14}},//sand
    {{1,15},{1,15},{1,15},{1,15},{1,15},{1,15}},//stone
    {{7,15},{7,15},{7,15},{7,15},{7,15},{7,15}},//brick
    {{5,14},{5,14},{4,14},{4,14},{4,14},{4,14}},//wood
    {{5,15},{6,15},{6,15},{6,15},{6,15},{6,15}},//cement
    {{2,15},{2,15},{2,15},{2,15},{2,15},{2,15}},//dirt
    {{4,15},{4,15},{4,15},{4,15},{4,15},{4,15}},//plank
    {{2,11},{2,15},{4,11},{4,11},{4,11},{4,11}},//snow
    {{1,12},{1,12},{1,12},{1,12},{1,12},{1,12}},//glass
    {{4,13},{2,15},{2,15},{2,15},{2,15},{2,15}},//cobble
    {{0,6},{0,6},{0,6},{0,6},{0,6},{0,6}},//light_stone
    {{1,14},{1,14},{1,14},{1,14},{1,14},{1,14}},//dark_stone
    {{9,14},{9,14},{9,14},{9,14},{9,14},{9,14}},//chest
    {{4,7},{4,7},{5,7},{5,7},{5,7},{5,7}},//leaves
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//cloud
    {{13,9},{0,0},{0,0},{0,0},{0,0},{0,0}},//TALL_GRASS
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//YELLOW_FLOWER
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//RED_FLOWER
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//PURPLE_FLOWER
    {{12,15},{0,0},{0,0},{0,0},{0,0},{0,0}},//SUN_FLOWER
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//WHITE_FLOWER
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//BLUE_FLOWER
    {{1,14},{1,14},{1,14},{1,14},{1,14},{1,14}},//BED_ROCK
    {},//water
    {{12,14},{0,0},{0,0},{0,0},{0,0},{0,0}},//mushroom
    {{6,9},{6,8},{7,8},{6,8},{6,8},{6,8}},//pumpkin
    {{5,11},{5,11},{6,11},{6,11},{6,11},{6,11}},//cacti
    {{10,9},{0,0},{0,0},{0,0},{0,0},{0,0}},//dried_grass
    {{5,14},{5,14},{5,8},{5,8},{5,8},{5,8}},//WHITE_BARK_TREE_WOOD
     {{9,9},{9,9},{8,9},{8,9},{8,9},{8,9}},//WHITE_BARK_TREE_LEAVES
     {{15,9},{0,0},{0,0},{0,0},{0,0},{0,0}},//clover
     {{8,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L0
     {{9,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L1
     {{10,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L2
     {{11,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L3
     {{12,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L4
     {{13,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L5
    {{14,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L6
    {{15,10},{0,0},{0,0},{0,0},{0,0},{0,0}},//seaweed_L7
    {{10,15},{9,15},{8,15},{8,15},{8,15},{8,15}},//TNT
    {{9,14},{9,14},{11,14},{10,14},{10,14},{10,14}},//workspace
    {{3,9},{0,0},{0,0},{0,0},{0,0},{0,0}},//torch
    {{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}},//lightstone
    };
const int ITEM_NUMS=ArrayLength<decltype(ITEM_UV)>::value;
Texture2D *BLOCK_TEXTURE;
vec2 FaceNumsPerAxis={16.0,16.0f};
bool is_NotBlock(int type)//判断是否为那些由两个图片叠加形成的方块
{
    switch(type){
    case TALL_GRASS:
    case YELLOW_FLOWER:
    case RED_FLOWER:
    case PURPLE_FLOWER:
    case SUN_FLOWER:
    case WHITE_FLOWER:
    case BLUE_FLOWER:
    case MUSHROOM:
    case DRIED_GRASS:
    case CLOVER:
    case SEAWEED_L0:
    case SEAWEED_L1:
    case SEAWEED_L2:
    case SEAWEED_L3:
    case SEAWEED_L4:
    case SEAWEED_L5:
    case SEAWEED_L6:
    case SEAWEED_L7:
    case TORCH:
        return 1;
    default:
        return 0;
    }
}


bool is_obstacle(int type)
{
    if (is_NotBlock(type)) {
        return 0;
    }
    switch (type) {
    case EMPTY:
    case CLOUD:
    case WATER:
        return 0;
    default:
        return 1;
    }
}

bool is_obstacle(const Block& block)
{
    return is_obstacle(block.id);
}

bool is_transparent(int type)
{
    if (type == EMPTY) {
        return 1;
    }
    if (is_NotBlock(type)) {
        return 1;
    }
    switch (type) {
    case EMPTY:
    case GLASS:
    case LEAVES:
        return 1;
    default:
        return 0;
    }
}

bool is_destructable(int type)
{
    switch (type) {
    case EMPTY:
    case CLOUD:
    case BED_ROCK:
    case WATER:
        //基岩
        return 0;
    default:
        return 1;
    }
}

bool is_functionalBlock(int type)
{
    switch (type)
    {
    case TNT:
    case WORKSPACE:
        return 1;
    default:
        return 0;
    }
}

bool is_Distinguish_Front(int type)
{
    switch (type)
    {
    case TNT:
    case WORKSPACE:
    case PUMPKIN:
        return 1;
    default:
        return 0;
    }
}

bool is_Plantable(int type)
{
    switch (type)
    {
    case DIRT:
    case SAND:
    case GRASS:
    case SNOW:
        return 1;
    default:
        return 0;
    }
}

bool is_Lightable(int type)
{
    switch (type)
    {
    case TORCH:
    case LIGHTSTONE:
        return 1;
    default:
        return 0;
    }
}
