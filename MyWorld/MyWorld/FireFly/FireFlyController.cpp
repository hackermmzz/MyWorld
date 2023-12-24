#include "FireFlyController.h"

FireFlyController::FireFlyController()
{
	//////////////////////////////////初始化全局随机数生成器
	static bool init = 0;
	if (!init)
	{
		init = 1;
		FireFlyRandGenerator.SetSeed(gettime());
		
	}
	//////////////////////////////////
	speed = FireFlyRandGenerator.rand(FireFlyMinSpeed,FireFlyMaxSpeed)/10.0;
	actions.AddState(BORN, new FireFlyBorn(currentPos, speed));
	actions.AddState(REST, new FireFlyRest);
	actions.AddState(FLYAROUND, new FireFlyFlyAround(currentPos,speed));
}

void FireFlyController::Born(const vec3& pos)
{
	currentPos = pos;
	actions.SwitchState(BORN);
}

FireFlyController::~FireFlyController()
{
	actions.ReleaseAllState();
}
