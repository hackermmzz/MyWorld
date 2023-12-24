#version 460 core
layout(location=0)in vec3  pos;
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
uniform vec3 offset;
const float scale=1.001;
void main()
{
gl_Position=vp*vec4((pos*scale+offset),1.0);
}