#pragma once
#include"../globalsource.h"
#include"../world.h"
extern const int FireFlyMaxNums;//场景最多含1000个萤火虫
extern vec3 FireFlyPos[];
extern int FireFlyGenerateMinNumPerGrass;
extern int FireFlyGenerateMaxNumPerGrass;
extern int FireFlyFollowArea;
extern int FireFlyFlyBackArea;
extern int FireFlySearchArea;
extern int FireFlyMaxSpeed;
extern int FireFlyMinSpeed;
extern Random FireFlyRandGenerator;
//////////////////////////////////////////
enum FireFlyState {
	BORN,
	REST,
	FLYAROUND,
	FOLLOW,
	FLYBACK,
	DIE
};
using FireFlyAction = FSMAction<FireFlyState>;
bool FireFlyCheck(const vec3& pos);