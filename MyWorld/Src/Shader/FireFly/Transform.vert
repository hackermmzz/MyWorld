#version 460 core
layout(location=0)in vec3 info_;
layout(location=1)in vec3 pos_;
layout(location=2)in vec3 target_;
out vec3 info;
out vec3 CurrentPos;
out vec3 CurrentTarget;
void main()
{
info=info_;
CurrentPos=pos_;
CurrentTarget=target_;
}