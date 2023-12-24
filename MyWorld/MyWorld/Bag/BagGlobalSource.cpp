#include"BagGlobalSource.h"
int BagColumn = 16;
int BagRow=16;
vector<QIcon*>ItemIcons;
map<vector<int>, ivec2>TransitionTable;
int BagItems[256];
WorkSpaceBoard* workSpaceBoard;
ItemBoard* itemBoard;
int ItemBoardCurrentSelectedItem = 0;
int MyBagCurrentSelectedItem = 0;
Bag* MyBag;