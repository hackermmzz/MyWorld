#pragma once
#include"globalsource.h"
#include"GlobalLight/GlobalLightSource.h"
#include"frustumcull.h"
struct MyWorldPointLight {
	vec4 pos;
	vec4 color;
};
void DrawGbuffer();
int GeneratePointLightSsbo();
vec3 GetLightBlockColor(Block& block);