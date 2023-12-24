#include "rolemove.h"


void RoleMove::Enter()
{
    last_time=gettime();
}

void RoleMove::Execute()
{
    vec3&camera_pos=camera.position;
    vec3 pre_position=camera_pos;
    auto time=gettime();
    auto delta_time=(time-last_time)/1000.0;
    if (delta_time * RoleMoveSpeed >= 1)return;
    last_time=time;
    /////////////////////////////判断移动方向
    if(RoleMoveDirection&FORWARD)
    camera.processKeyBoard(FORWARD,delta_time);
    if(RoleMoveDirection&LEFT)
    camera.processKeyBoard(LEFT,delta_time);
    if(RoleMoveDirection&BACKWARD)
    camera.processKeyBoard(BACKWARD,delta_time);
    if(RoleMoveDirection&RIGHT)
    camera.processKeyBoard(RIGHT,delta_time);
    camera_pos.y=pre_position.y;
    /////////////////////////////矫正人物位置
    CorrectRolePosition();
}

void RoleMove::Exit()
{

}

void CorrectRolePosition()
{
    static float minus = std::numeric_limits<float>::epsilon();
    auto&camera_pos = camera.position;
    int y = floor(camera_pos.y - RoleBox.h);
    int y_end = floor(camera_pos.y);
    //正z
    for (; y <= y_end; ++y) {
        if (is_obstacle(world->GetBlock(floor(camera_pos.x), y, floor(camera_pos.z + RoleBox.r)))) {
            camera_pos.z = floor(camera_pos.z + RoleBox.r) - minus - RoleBox.r;
        }
        //负z
        if (is_obstacle(world->GetBlock(floor(camera_pos.x),y, floor(camera_pos.z - RoleBox.r))))
        {
            camera_pos.z = floor(camera_pos.z - RoleBox.r) + 1.0 + minus + RoleBox.r;
        }
        //正x
        if (is_obstacle(world->GetBlock(floor(camera_pos.x + RoleBox.r), y, floor(camera_pos.z)))) {
            camera_pos.x = floor(camera_pos.x + RoleBox.r) - minus - RoleBox.r;
        }
        //负x
        if (is_obstacle(world->GetBlock(floor(camera_pos.x - RoleBox.r),y, floor(camera_pos.z))))
        {
            camera_pos.x = floor(camera_pos.x - RoleBox.r) + 1.0 + minus + RoleBox.r;
        }
    }
}
