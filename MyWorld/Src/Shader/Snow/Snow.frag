#version 460 core
uniform sampler2D snow;
precision mediump float;
out vec4 color;
void main()
{
vec4 snowColor=texture2D(snow,gl_PointCoord);
if(snowColor.a<0.1)discard;
color=snowColor;
}