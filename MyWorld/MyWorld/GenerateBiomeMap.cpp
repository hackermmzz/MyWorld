#include "GenerateBiomeMap.h"
float GenerateBiomeMap(ivec2&position,BiomeType&biome)
{
	/////////////////////////////////////////////温湿度等级对照表
	thread_local static vector<float>TemperatureLevelMap;
	thread_local static vector<float>HumidityLevelMap;
	thread_local static vector<vector<BiomeType>>BiomeTypeMap;
	thread_local static bool init = 0;
     static int FBM = 4;
	if (!init)
	{
		init = 1;
		ConfigBiomeMap(TemperatureLevelMap, HumidityLevelMap, BiomeTypeMap);
	}
	/////////////////////////////////////////////
	vec2 pos = vec2(position.x,position.y);
	/////////////////////////////////////////////先判断为陆地还是海洋
	float Continental = ContinentalNoise.octave2D_01(pos.x / CONTINENTALNOISEFREQ, pos.y / CONTINENTALNOISEFREQ, FBM);
	if (Continental < OCEAN_WEIGHT) {
		biome = OCEAN;
	}
	else {
		/////////////////////////////////////////////产生温度和湿度
		static int temperatureDiv = TEMPERATURENOISEFREQ * SECTION_SIZE;
		static int humidityDiv = HUMIDITYNOISEFREQ * SECTION_SIZE;
		static float minus = std::numeric_limits<float>::epsilon();
		float temperature = TemperatureNoise.octave2D_11(pos.x / temperatureDiv, pos.y / temperatureDiv, FBM)-minus;
		float humidity = HumidityNoise.octave2D_11(pos.x / humidityDiv, pos.y / humidityDiv, FBM)-minus;
		//获得温度和湿度等级
		int temperatureLevel = upper_bound(TemperatureLevelMap.begin(), TemperatureLevelMap.end(), temperature) - TemperatureLevelMap.begin();
		int humidityLevel = upper_bound(HumidityLevelMap.begin(), HumidityLevelMap.end(), humidity) - HumidityLevelMap.begin();
		biome=BiomeTypeMap[temperatureLevel][humidityLevel];
	}
	return Continental;
}

void ConfigBiomeMap(vector<float>& TemperatureLevelMap, vector<float>& HumidityLevelMap, vector<vector<BiomeType>>& BiomeTypeMap)
{
	TemperatureLevelMap = {-0.6,-0.3,0.0,0.5,1.0};
	HumidityLevelMap = { -0.8,-0.5,0.0,0.5,1.0 };
	BiomeTypeMap = vector<vector<BiomeType>>(TemperatureLevelMap.size(),vector<BiomeType>(HumidityLevelMap.size()));
	////////////////////////////////
	BiomeTypeMap[0][0] = SNOWFIELD;
	BiomeTypeMap[0][1] = SNOWFIELD;
	BiomeTypeMap[0][2] = SNOWFIELD;
	BiomeTypeMap[0][3] = SNOWFIELD;
	////
	BiomeTypeMap[1][0] = PLAIN;
	BiomeTypeMap[1][1] =PLAIN;
	BiomeTypeMap[1][2] = PLAIN;
	BiomeTypeMap[1][3] = PLAIN;
	////
	BiomeTypeMap[2][0] = PLAIN;
	BiomeTypeMap[2][1] = PLAIN;
	BiomeTypeMap[2][2] = FOREST;
	BiomeTypeMap[2][3] = FOREST;
	////
	BiomeTypeMap[3][0] = DESERT;
	BiomeTypeMap[3][1] = DESERT;
	BiomeTypeMap[3][2] = DESERT;
	BiomeTypeMap[3][3] = DESERT;
	////////////////////////////////
}
