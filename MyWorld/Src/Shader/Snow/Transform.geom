#version 460 core
layout(points)in;
layout(points,max_vertices=10)out;
uniform sampler1D random;
uniform float deltaTime;
uniform vec3 rolePos;
in vec3 info[];
in vec3 CurrentPos[];
in vec3 CurrentDir[];
out float type;
out float life;
out float age;
out vec3 pos;
out vec3 dir;
/////////////////////////////////////
#define Launcher 0.0
#define Snow 1.0
#define Laucher_Max_Life 1000.0
#define Laucher_Min_Life 100.0
#define Snow_Max_Life 8000.0
#define Snow_Min_Life 4000.0
#define Render_Radius 20
const float Init_Y=Render_Radius/5;
const float End_Y=Render_Radius/3;
/////////////////////////////////////
vec3 GetRandDir(float uv)
{
return texture(random,uv).xyz;
}
float GetRand(float uv)
{
return -texture(random,uv).y;
}
float GetSnowRandLife(float  uv)
{
float val=GetRand(uv);
return mix(Snow_Max_Life,Snow_Min_Life,val);
}
void main()
{
type=info[0].x;
life=info[0].y;
age=info[0].z+deltaTime;
float uv=1/(deltaTime+1.0/(pos.x+pos.z));
if(type==Launcher)
{
if(age>=life)
{
type=Snow;
life=GetSnowRandLife(uv);
age=0;
pos=rolePos+vec3(CurrentPos[0].x,Init_Y,CurrentPos[0].z);
dir=GetRandDir(uv);
EmitVertex();
EndPrimitive();
type=Launcher;
life=info[0].y;
}
pos=CurrentPos[0];
EmitVertex();
EndPrimitive();
}
else 
{
pos=CurrentPos[0];
dir=CurrentDir[0];
if(rolePos.y-pos.y>End_Y)return;
if(age>life)
{
type=Snow;
life=GetSnowRandLife(uv);
age=0;
dir=GetRandDir(uv);
EmitVertex();
EndPrimitive();
}
else{
pos+=dir*(deltaTime/400.0);
EmitVertex();
EndPrimitive();
}
}
}