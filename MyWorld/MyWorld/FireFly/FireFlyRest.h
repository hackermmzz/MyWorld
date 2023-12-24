#pragma once
#include"FireFlyGlobalSource.h"
struct FireFlyRest :FireFlyAction {
	FireFlyRest() = default;
	// Í¨¹ý FSMAction ¼Ì³Ð
	int RestTime;
	long long lastTime;
	void Enter() override;
	void Execute() override;
	void Exit() override;
};
