#version 460 core
layout(points)in;
layout(points,max_vertices=10)out;
uniform sampler1D random;
uniform sampler1D random2;
uniform float deltaTime;
uniform float randVal;
uniform vec3 rolePos;
uniform int PlantNums;
layout(std430)buffer PLANTS{
vec4 plants[];
};
in vec3 info[];
in vec3 CurrentPos[];
in vec3 CurrentTarget[];
out float type;
out float life;
out float age;
out vec3 pos;
out vec3 target;
/////////////////////////////////////
#define Launcher 0.0
#define FireFly 1.0
#define Laucher_Max_Life 1000.0
#define Laucher_Min_Life 100.0
#define FireFly_Max_Life 8000.0
#define FireFly_Min_Life 5000.0
#define Render_Radius 20
const float Init_Y=Render_Radius/5;
const float End_Y=Render_Radius/3;
/////////////////////////////////////
float GetRand(float uv)
{
return texture(random,uv).x;
}
vec3 GetRandTarget(float uv)
{
float rand=GetRand(uv);
return plants[int(PlantNums*rand)].xyz+texture(random2,uv).xyz;
}
float GetFireFlyRandLife(float  uv)
{
float val=GetRand(uv);
return mix(FireFly_Max_Life,FireFly_Min_Life,val);
}
void main()
{
type=info[0].x;
life=info[0].y;
age=info[0].z+deltaTime;
float uv=1/(deltaTime+1.0/(pos.x+pos.z))+randVal;
if(type==Launcher)
{
if(age>=life)
{
type=FireFly;
life=GetFireFlyRandLife(uv);
age=0;
pos=rolePos+vec3(CurrentPos[0].x,Init_Y,CurrentPos[0].z);
target=GetRandTarget(uv);
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
target=CurrentTarget[0];
if(rolePos.y-pos.y>End_Y||age>life)return;
else{
pos=mix(pos,target,age/life*0.01);
EmitVertex();
EndPrimitive();
}
}
}