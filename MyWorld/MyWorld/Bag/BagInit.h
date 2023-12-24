#pragma once
#include"BagGlobalSource.h"
#include"../EventProcess.h"
#include"UpdateItemBoard.h"
void BagInit();
bool operator<(vector<int>& v1, vector<int>& v2);
void GenerateExchangeTable();
void GenerateAllBlockicons();
void WorkSpaceBoardInit();
void ItemBoardInit();
void MyBagInit();
ivec2 FindExchangeTable(vector<int>& id);