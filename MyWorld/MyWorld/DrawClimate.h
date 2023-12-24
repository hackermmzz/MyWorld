#pragma once
#include"GlobalLight/UpdateLight.h"
#include"drawcloud.h"
/// /////////////////////////////////////////////
struct SnowParticle {
	float type;
	float life;
	float age;
	vec3 pos;
	vec3 dir;
};
struct RainParticle
{
	float type;
	float life;
	float age;
	vec3 pos;
};
/// /////////////////////////////////////////////
void DrawClimate();
void DrawSnow();
void DrawRain();