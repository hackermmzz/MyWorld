#include"GlobalLightSource.h"
long long TimePerDay =10 * 60 * 1000;//10����Ϊ1��
float TimeOfDay = TimePerDay/2;//��ʼΪ12��
float CurrentTime;
vec3 SunLight;
vec3 SunPos;
float Brightness=0.1;
float StarBrightness=0.0; 
float exposure = 1.0;