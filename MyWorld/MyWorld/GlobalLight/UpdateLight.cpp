#include "UpdateLight.h"
void UpdateLight()
{
	static vec3 SunLightHighColor = vec3{1.0,0.6,0.0};
	static vec3 SunLightLowColor = vec3{0.8,0.4,0.4}/2;
	static float brightnessMin = 0.1,brightnessMax = 1.0;
	TimeOfDay += render_time;
	TimeOfDay=fmod(TimeOfDay,TimePerDay);
	CurrentTime=TimeOfDay*24/TimePerDay;
	/////////////////////////////计算光强和位置
	////////////////////////////
	float angle = PI * CurrentTime / 12;
	float posy = -cos(angle);
	float posx = -sin(angle);
	SunPos = vec3{posx,posy,-1 }.normalize();
	if (posy < 0)
	{
		StarBrightness = 1.0 * (-posy);
	}
	else
	{
		Brightness = brightnessMin*(1-posy)+brightnessMax*posy;
		SunLight = SunLightLowColor.mix(SunLightHighColor,posy);
	}
}
