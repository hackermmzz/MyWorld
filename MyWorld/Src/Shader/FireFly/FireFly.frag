#version 460 core
uniform sampler2D FireFly;
precision mediump float;
out vec4 color;
void main()
{
vec4 snowColor=texture2D(FireFly,gl_PointCoord);
if(snowColor.a<0.1)discard;
color=snowColor;
}