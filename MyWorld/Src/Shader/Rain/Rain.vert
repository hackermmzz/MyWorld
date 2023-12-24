#version 460 core
precision mediump float;
layout(location=0)in vec3 pos;
layout(std140)uniform VP
{
mat4 vp;
mat4 projection;
mat4 view;
};
uniform vec3 eye;
const float RainSize=20.0;
const float RainMaxSize=10.0;
void main()
{
gl_PointSize=max(RainSize*1/(length(pos-eye)),RainMaxSize);
gl_Position=vp*vec4(pos,1.0);
}