#include"BackwardProcess.h"
void BackwardProcess()
{
    //////////////////////////////////////更新ItemBoard
    UpdateItemBoard();
    //////////////////////////////////////删除多余的区块
    world->RemoveExtraChunks();
    //////////////////////////////////////加载缺失的区块
    UpdateAllChunks();
}
