#version 460 core
uniform sampler2D rain;
precision mediump float;
out vec4 color;
void main()
{
vec4 rainColor=texture2D(rain,gl_PointCoord);
if(rainColor.a<0.1)discard;
color=rainColor;
}