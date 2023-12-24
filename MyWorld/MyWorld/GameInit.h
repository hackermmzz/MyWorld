#ifndef GAMEINIT_H
#define GAMEINIT_H
#include"myworld.h"
#include"stdlib.h"
#include"world.h"
#include"generateterrain.h"
#include"generateface.h"
#include"generateblock.h"
#include"fstream"
#include"generatecloud.h"
#include"generateDecoration.h"
#include"functional"
#include"Bag/BagInit.h"
#include"updatechunk.h"
#include"RoleController/rolecontorller.h"
using std::ifstream;
using std::function;
void GameInit();
void InitBlock();//初始化所有的block
void InitCloud();//加载云朵
void InitNoiseGenerator();
void InitChunkRenderProgram();
void InitCloudRenderProgram();
void InitWaterRenderProgram();
void InitGBuffer();
void InitWorld();
void InitRole();
#endif // GAMEINIT_H
