#pragma once
#include"FireFlyGlobalSource.h"
struct FireFlyRest :FireFlyAction {
	FireFlyRest() = default;
	// ͨ�� FSMAction �̳�
	int RestTime;
	long long lastTime;
	void Enter() override;
	void Execute() override;
	void Exit() override;
};
