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
void CorrectRolePosition();//��ǰ�����ҷ����������λ��
#endif // ROLEMOVE_H
