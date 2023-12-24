#version 460 core
layout(points)in;
layout(points,max_vertices=10)out;
uniform sampler1D random;
uniform float deltaTime;
uniform vec3 rolePos;
in vec3 info[];
in vec3 CurrentPos[];
out float type;
out float life;
out float age;
out vec3 pos;
/////////////////////////////////////
#define Launcher 0.0
#define Rain 1.0
#define Laucher_Max_Life 1000.0
#define Laucher_Min_Life 700.0
#define Rain_Max_Life 8000.0
#define Rain_Min_Life 4000.0
#define Render_Radius 20
const float Init_Y=Render_Radius/5;
const float End_Y=Render_Radius/3;
/////////////////////////////////////
float GetRand(float uv)
{
return texture(random,uv).r;
}
float GetRainRandLife(float  uv)
{
float val=GetRand(uv);
return mix(Rain_Max_Life,Rain_Min_Life,val);
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
type=Rain;
life=GetRainRandLife(uv);
age=0;
pos=rolePos+vec3(CurrentPos[0].x,Init_Y,CurrentPos[0].z);
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
if(rolePos.y-pos.y>End_Y)return;
pos.y+=-1.0*(deltaTime/400.0);
EmitVertex();
EndPrimitive();
}
}