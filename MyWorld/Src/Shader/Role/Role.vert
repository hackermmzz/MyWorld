#version 460 core
layout(location=0)in vec3 pos;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 uv;
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
uniform mat4 model;
out vec2 TexCoord;
out vec3 Normal;
out vec4 Position;
////////////////////////
void main()
{
TexCoord=uv;
Normal=normal;
//////////////////////////
vec4 PosToWorld=model*vec4(pos,1.0);
vec4 PosToEye=view*PosToWorld;
Position=vec4(PosToWorld.xyz,PosToEye.z);
gl_Position=projection*PosToEye;
}