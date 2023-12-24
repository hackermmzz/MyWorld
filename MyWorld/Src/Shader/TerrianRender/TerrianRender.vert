#version 460 core
layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 uv;
///////////////////////////////////////////////
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
///////////////////////////
uniform vec3 eye;
uniform float FrogMaxDis;
uniform float FrogMinDis;
///////////////////////////Îí»¯²ÎÊý
///////////////////////////
out vec3 Normal;
out vec2 TexCoord;
out vec4 Position;
out float FrogFactor;       
void main()
{
Normal=normal;
TexCoord=uv;
vec4 PosToEye=view*vec4(position,1.0);
gl_Position=projection*PosToEye;
Position=vec4(position,PosToEye.z);
FrogFactor=clamp((length(eye-position)-FrogMinDis)/(FrogMaxDis-FrogMinDis),0.0,0.9);
}