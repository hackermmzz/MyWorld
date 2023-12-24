#include "roledrop.h"

void RoleDrop::Enter()
{
    last_time=gettime();
    speed=0;
}

void RoleDrop::Execute()
{
    static float minus = std::numeric_limits<float>::epsilon();
    auto time=gettime();
    auto delta_time=(time-last_time)/1000.0;
    last_time=time;
    /////////////////////////////掉落
    float delta_y =speed * delta_time;
    speed+=delta_time*10.0;
    speed = fmin(speed, 20);
    /////////////////////////////
    vec3 block_pos = camera.position.floor();
    int y = floor((camera.position.y - RoleBox.h));
    int y_end = floor(camera.position.y - RoleBox.h - delta_y);
    for (; y>= y_end; --y)
    {
        if (is_obstacle(world->GetBlock(block_pos.x, y, block_pos.z)))
        {
            camera.position.y=y+1+RoleBox.h+minus;
            SwitchState(STOP);
            return;
        }
    }
    camera.position.y -= delta_y;
}

void RoleDrop::Exit()
{

}

bool RoleDrop::AllowSwitchState(const RoleState& state)
{
    if (state == JUMP)return 0;
    return 1;
}