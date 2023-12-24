#pragma once
#include"globalsource.h"
#include"chunk.h"
///////////////////////////////////////////////////
float GenerateBiomeMap(ivec2&position,BiomeType&biome);
void ConfigBiomeMap(vector<float>& TemperatureLevelMap, vector<float>& HumidityLevelMap,vector<vector<BiomeType>>&BioTypeMap);