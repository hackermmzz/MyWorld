#version 460 core
layout(location=0)in vec3 pos;
layout(location=1)in vec2 uv;
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
/////////////////////////
out vec2 TexCoord;
out vec3 FragPos;
/////////////////////////
void main()
{
TexCoord=uv;
FragPos=pos;
gl_Position=vp*vec4(pos,1.0);
}