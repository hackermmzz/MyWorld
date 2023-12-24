#pragma once
#include"FireFlyRest.h"
#include"FireFlyBorn.h"
#include"FireFlyFlyAround.h"
struct FireFlyController {
	FSM<FireFlyState> actions;
	float speed;
	vec3 currentPos;
	FireFlyController();
	void Born(const vec3& pos);
	~FireFlyController();
};