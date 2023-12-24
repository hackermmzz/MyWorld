#version 460 core
uniform sampler2D diffuse0;
in vec2 TexCoord;
in vec3 Normal;
in vec4 Position;
layout(location=0)out vec4 color;
layout(location=1)out vec4 position;
layout(location=2)out vec4 normal;
void main()
{
color=vec4(texture(diffuse0,TexCoord).rgb,1.0);
normal=vec4(Normal,0.0);
position=Position;
}