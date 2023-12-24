#pragma once
#include"FireFlyGlobalSource.h"
#include"../GlobalLight/GlobalLightSource.h"
struct FireFlyParticle {
	float type;
	float life;
	float age;
	vec3 pos;
	vec3 target;
};
void DrawFireFly();
int GetRoleAroundPlant();