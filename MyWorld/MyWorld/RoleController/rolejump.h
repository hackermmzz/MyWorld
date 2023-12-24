#ifndef ROLEJUMP_H
#define ROLEJUMP_H
#include"rolecontrollersource.h"
struct RoleJump:RoleAction
{
    long long last_time;
    float speed;
    void Enter();
    void Execute();
    void Exit();
    bool AllowSwitchState(const RoleState& state);
};

#endif // ROLEJUMP_H
