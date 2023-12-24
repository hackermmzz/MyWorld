#include "rolecontorller.h"
//////////////////////////////////////
RoleController rolecontroller;
////////////////////////////////////////
RoleController::RoleController()
{
    //////////////////////////////////////////////
    jdfsm.AddState(STOP,new RoleStop(1));
    jdfsm.AddState(JUMP, new RoleJump);
    jdfsm.AddState(DROP, new RoleDrop);
    ////////////////////////////////////////////
    mvfsm.AddState(STOP, new RoleStop(0));
    mvfsm.AddState(MOVE,new RoleMove);
    ///////////////////////////////////////////
    buildfsm.AddState(STOP, new RoleStop(0));
    buildfsm.AddState(DESTROY_BLOCK, new RoleChangeBlock);
    buildfsm.AddState(FUNCTION_BLOCK, new RoleFunctionBlock);
    /////////////////////////////////////////////
    jdfsm.SwitchState(STOP);
    mvfsm.SwitchState(STOP);
    buildfsm.SwitchState(STOP);
}

void RoleController::Run()
{
    jdfsm.Run();
    mvfsm.Run();
    buildfsm.Run();
}

