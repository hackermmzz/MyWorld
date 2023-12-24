#ifndef ROLEDROP_H
#define ROLEDROP_H
#include"rolecontrollersource.h"
struct  RoleDrop:RoleAction
{
    long long last_time;
    float speed;
    void Enter();
    void Execute();
    void Exit();
    bool AllowSwitchState(const RoleState& state);
};

#endif // ROLEDROP_H
