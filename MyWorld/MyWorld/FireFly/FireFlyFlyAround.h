#pragma once
#include"FireFlyGlobalSource.h"
struct FireFlyFlyAround :FireFlyAction {
	FireFlyFlyAround(vec3& currentPos,float& speed);
	// ͨ�� FSMAction �̳�
	vec3*currentPos;
	float* speed;
	void Enter() override;
	void Execute() override;
	void Exit() override;
};