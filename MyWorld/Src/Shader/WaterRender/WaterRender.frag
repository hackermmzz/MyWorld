#version 460 core
in vec2 TexCoord;
in vec3 FragPos;
out vec4 color;
//////////////////////////
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
uniform sampler2D screenColor;
uniform sampler2D screenDepth;
uniform samplerCube skybox;
uniform sampler2D wave1;
uniform sampler2D wave2;
uniform float time;
uniform vec3 camera;
//////////////////////////
const float water_reflect_factor=0.2;
const float water_refract_factor=1.333;
const int maxSteps=64;
const int blur=1;
const float separation[blur*2+1][blur*2+1]={
{0.0625,0.125,0.0625},
{0.125,0.25,0.125},
{0.0625,0.125,0.0625},
};
/////////////////////////计算菲涅尔系数
float fresnelSchlick(float cosTheta)
{
return mix(pow(1.0-cosTheta,5.0),1.0,water_reflect_factor);
}
//////////////////////////步进算法获得颜色
vec4 RayMarchGetColor(vec3 dir,float maxDistance)
{
vec4 PosBegin=vec4(FragPos,1.0);
vec4 PosEnd=vec4(PosBegin.xyz+dir*maxDistance,1.0);
PosBegin=view*PosBegin;
PosEnd=view*PosEnd;
float z_begin=PosBegin.z,z_end=PosEnd.z;
PosBegin=projection*PosBegin,PosEnd=projection*PosEnd;
vec2 uvBegin=vec2(PosBegin.xy/PosBegin.w)*0.5+0.5;
if(z_begin<texture(screenDepth,uvBegin).w)discard;
vec2 uvEnd=vec2(PosEnd.xy/PosEnd.w)*0.5+0.5;
ivec2 size=textureSize(screenColor,0);
ivec2 begin=ivec2(uvBegin*size),end=ivec2(uvEnd*size);
///////////////////////////////////////////
ivec2  delta=end-begin;
float useX=abs(delta.x)>abs(delta.y)?1:0;
float loop=mix(abs(delta.y),abs(delta.x),useX);
loop=min(maxSteps,loop);
vec2 uv=vec2(0.0);
bool hit=false;
for(float i=1;i<=loop;i+=1.0)
{
float percent=i/loop;
float current_z=mix(z_begin,z_end,percent);
uv=mix(uvBegin,uvEnd,percent);
float depth=texture(screenDepth,uv).w;
float distance=depth-current_z;
if(abs(distance)<0.2)
{
hit=true;
break;
}
}
/////////////////////////////
if(hit){
vec3 color=vec3(0.0);
for(int x=-blur;x<=blur;++x)
{
for(int y=-blur;y<=blur;++y)
{
color=texture(screenColor,uv+vec2(x,y)/size).rgb*separation[x+blur][y+blur];
}
}
return vec4(color,0.0);
}
/////////////////////////////
return vec4(1.0);
}
//////////////////////////获取到反射到的片段
vec3 ReflectColor(vec3 fragToview,vec3 normal)
{
vec3 reflectDir=reflect(-fragToview,normal);
////////////////////////////////
vec4 res=RayMarchGetColor(reflectDir,20);
if(res.a==0.0)return res.rgb;
else
{
return texture(skybox,reflectDir).rgb*0.5;
}
}
//////////////////////////////////////
vec3 RefractColor(vec3 fragToview,vec3 normal)
{
vec3 refractDir=refract(-fragToview,normal,water_refract_factor);
vec4 color=RayMarchGetColor(refractDir,10);
if(color.a==0.0)return color.rgb;
return vec3(0.0,0.0,0.1);
}
//////////////////////////////////////
vec3 CanculateNormal(vec2 uv)
{
vec3 wave1=texture(wave1,uv).rgb;
vec3 wave2=texture(wave2,uv).rgb;
vec3 waveNormal=normalize(wave1+wave2);
vec3 normal=mix(vec3(0.0,1.0,0.0),waveNormal,vec3(0.3));
return normalize(normal);
}
//////////////////////////////////////
void main()
{
vec3 FragToView=normalize(camera-FragPos);
/////////////////////////////
vec2 uv=(FragPos.xz+vec2(1.0,1.0)*time)/100.0;
vec3 normal=CanculateNormal(uv);
/////////////////////////////获得菲尼尔系数
float theta=dot(FragToView,normal);
float fresnel=fresnelSchlick(theta);
/////////////////////////////获得反射到的颜色
vec3 reflectColor=ReflectColor(FragToView,normal);
//////////////////////////////获得折射的颜色
vec3 refractColor=RefractColor(FragToView,normal);
///////////////////////////////混合颜色
vec3 waterBaseColor=mix(refractColor,reflectColor,fresnel);
//////////////////////////////
color=vec4(waterBaseColor,1.0);
}