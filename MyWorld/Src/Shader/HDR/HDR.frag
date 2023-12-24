#version 460 core
uniform sampler2D bloom;
uniform sampler2D screen;
uniform float exposure;
in vec2 TexCoord;
out vec4 color;
const vec3 Gamma=vec3(1.0/2.2);
void main()
{
vec3 screenColor=texture2D(screen,TexCoord).rgb;
vec3 bloomColor=texture2D(bloom,TexCoord).rgb;
screenColor+=bloomColor;
screenColor=vec3(1.0)-exp(-screenColor * exposure);
color=vec4(pow(screenColor,Gamma),1.0);
}