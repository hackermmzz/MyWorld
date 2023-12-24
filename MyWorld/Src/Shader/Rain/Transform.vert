#version 460 core
layout(location=0)in vec3 info_;
layout(location=1)in vec3 pos_;
out vec3 info;
out vec3 CurrentPos;
void main()
{
info=info_;
CurrentPos=pos_;
}