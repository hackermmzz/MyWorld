#include "rolejump.h"
void RoleJump::Enter()
{
    last_time=gettime();
    speed = RoleJumpSpeed;
}

void RoleJump::Execute()
{
    static float minus = std::numeric_limits<float>::epsilon();
    auto time=gettime();
    auto delta_time=(time-last_time)/1000.0;
    last_time=time;
    /////////////////////////////跳跃
    float delta_y = speed * delta_time;
    speed -= delta_time * 10;
    /////////////////////////////
    vec3 block_pos = camera.position.floor();
    int y = ceil(camera.position.y);
    int y_end = floor(camera.position.y + delta_y);
    for (;y <= y_end; ++y) {
        if (is_obstacle(world->GetBlock(block_pos.x, y, block_pos.z)))
        {
            camera.position.y = y - minus;
            SwitchState(DROP);
            return;
        }
    }
    if (y >= y_end)
        camera.position.y += delta_y;
    if (speed <= 0)SwitchState(DROP);
}

void RoleJump::Exit()
{

}

bool RoleJump::AllowSwitchState(const RoleState& state)
{
    if (state == JUMP)return 0;
    return 1;
}



