#ifndef ROLEDESTROY_H
#define ROLEDESTROY_H
#include"rolecontrollersource.h"
#include"../Bag/BagGlobalSource.h"
struct RoleChangeBlock:RoleAction
{
    void Enter();
    void Execute();
    void Exit();
};
bool CheckBlockAroundIsWater(const ivec3& pos);
void FillWaterAroundWithWater(ivec3& pos,vector<ivec3>&UpdatedSection);
#endif // 
