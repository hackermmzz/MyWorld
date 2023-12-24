#pragma once 
#include"FireFlyGlobalSource.h"
struct FireFlyBorn:FireFlyAction
{
	vec3 targetPos;
	vec3 speed_v;
	vec3*currentPos;
	float*speed;
	long long lasttime;
	FireFlyBorn(vec3&currentPos,float&speed);
	void Enter() override;
	void Execute() override;
	void Exit() override;
};