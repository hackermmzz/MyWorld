#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H
#include"../globalsource.h"
#include"../generateterrain.h"
#include"rolemove.h"
#include"rolecontrollersource.h"
#include"rolestop.h"
#include"roledrop.h"
#include"rolejump.h"
#include"roledestroyblock.h"
#include"roleFunctionBlock.h"
///////////////////////////////////////
struct RoleController{
    RoleFSM jdfsm;
    RoleFSM mvfsm;
    RoleFSM buildfsm;
    RoleController();
    void Run();
};
extern RoleController rolecontroller;
#endif // ROLE_H
