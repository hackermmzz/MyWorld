#ifndef ROLECONTROLLERSOURCE_H
#define ROLECONTROLLERSOURCE_H
#include"../globalsource.h"
#include"../generateterrain.h"
#include"../generateface.h"
#include"../../workspaceboard.h"
struct Cylinder
{
    float r;
    float h;
};
enum RoleState{
    STOP,
    MOVE,
    JUMP,
    DROP,
    DESTROY_BLOCK,
    FUNCTION_BLOCK,
};
using RoleAction=FSMAction<RoleState>;
void UpdateSectionFaceNearBlock(int x, int y, int z);///////////////////////����һ��block�������ٽ�section
void UpdateBlockChangedMap(const ivec3& pos, Block& block);
using RoleFSM=FSM<RoleState>;
extern size_t RoleMoveDirection;
extern Cylinder RoleBox;//����Բ�����Χ��
extern float RoleMoveSpeed;
extern float RoleJumpSpeed;
#endif // ROLECONTROLLERSOURCE_H
