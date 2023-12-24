#pragma once
#include"FireFlyGlobalSource.h"
struct FireFlyFlyAround :FireFlyAction {
	FireFlyFlyAround(vec3& currentPos,float& speed);
	// Í¨¹ý FSMAction ¼Ì³Ð
	vec3*currentPos;
	float* speed;
	void Enter() override;
	void Execute() override;
	void Exit() override;
};