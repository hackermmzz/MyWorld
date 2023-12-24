#pragma once
#include"../../BagButton.h"
#include"../globalsource.h"
#include"../../workspaceboard.h"
#include"../../itemboard.h"
#include"../../bag.h"
extern int BagColumn;
extern int BagRow;
extern vector<QIcon*>ItemIcons;
extern map<vector<int>, ivec2>TransitionTable;
extern int BagItems[256];
extern WorkSpaceBoard* workSpaceBoard;
extern ItemBoard* itemBoard;
extern int ItemBoardCurrentSelectedItem;
extern int MyBagCurrentSelectedItem;
extern Bag* MyBag;
/////////////////////////
