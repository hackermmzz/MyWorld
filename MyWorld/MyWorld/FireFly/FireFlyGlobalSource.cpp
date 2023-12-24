#include"FireFlyGlobalSource.h"
const int FireFlyMaxNums =1000;
vec3 FireFlyPos[FireFlyMaxNums];
int FireFlyGenerateMinNumPerGrass=0;
int FireFlyGenerateMaxNumPerGrass = 5;
int FireFlyFollowArea=1;
int FireFlyFlyBackArea=2;
int FireFlySearchArea=FireFlyFlyBackArea+1;
int FireFlyMaxSpeed=6;
int FireFlyMinSpeed=10;
Random FireFlyRandGenerator;

bool FireFlyCheck(const vec3& pos)
{
    return is_obstacle(world->GetBlock(floor(pos.x), floor(pos.y), floor(pos.z)));
}
