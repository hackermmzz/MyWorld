#include"GlobalLightSource.h"
long long TimePerDay =10 * 60 * 1000;//10分钟为1天
float TimeOfDay = TimePerDay/2;//开始为12点
float CurrentTime;
vec3 SunLight;
vec3 SunPos;
float Brightness=0.1;
float StarBrightness=0.0; 
float exposure = 1.0;