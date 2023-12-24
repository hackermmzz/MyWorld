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
const float SnowSize=20.0;
const float SnowMaxSize=10.0;
void main()
{
gl_PointSize=min(SnowSize*1/(length(pos-eye)),SnowMaxSize);
gl_Position=vp*vec4(pos,1.0);
}