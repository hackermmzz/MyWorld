#version 460 core
uniform sampler2D BiomeMap;
in vec2 TexCoord;
out vec4 color;
void main()
{
vec3  data=texture(BiomeMap,TexCoord).rgb;
color=vec4(vec3(data),0.5);
}