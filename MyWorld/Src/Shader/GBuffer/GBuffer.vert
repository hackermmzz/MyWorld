#version 460 core
layout(location=0)in vec2 pos;
layout(location=1)in vec2 uv;
//////////////////////////
out vec2 TexCoord;
void main()
{
TexCoord=uv;
gl_Position=vec4(pos,0.0,1.0);
}