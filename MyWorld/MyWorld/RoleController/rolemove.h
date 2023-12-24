#ifndef ROLEMOVE_H
#define ROLEMOVE_H
#include"rolecontrollersource.h"
struct  RoleMove:RoleAction
{
    long long last_time;
    void Enter();
    void Execute();
    void Exit();
};
void CorrectRolePosition();//在前后左右方向矫正人物位置
#endif // ROLEMOVE_H
