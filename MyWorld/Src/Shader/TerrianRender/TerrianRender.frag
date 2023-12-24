#version 460 core
/////////////////////////////////
in vec3 Normal;
in vec2 TexCoord;
in float FrogFactor;
in vec4 Position;
layout(location=0)out vec4 color;
layout(location=1)out vec4 position;
layout(location=2)out vec4 normal;
/////////////////////////////////
uniform sampler2D sampler;
/////////////////////////////////
void main()
{
vec4 tex=texture(sampler,TexCoord);
if(tex.a==0.0)discard;
color=mix(vec4(tex.rgb,1.0),vec4(1.0),FrogFactor);
normal=vec4(Normal,0.0);
position=Position;
}