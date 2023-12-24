#ifndef ROLESTOP_H
#define ROLESTOP_H
#include"rolecontrollersource.h"
struct  RoleStop:RoleAction
{
    bool controlDrop;
    RoleStop(bool controlDrop);
    void Enter();
    void Execute();
    void Exit();
};

#endif // ROLESTOP_H
