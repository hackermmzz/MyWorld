#version 460 core
in vec2 TexCoord;
uniform  sampler2D gbuffer0;//ÑÕÉ«
uniform  sampler2D gbuffer1;//Î»ÖÃ
uniform  sampler2D gbuffer2;//normal
uniform  vec3 LightPos;
uniform  vec3 Light;
uniform  float Brightness;
out vec4 color;
void main()
{
//////////////////////////////
vec3 normal=texture2D(gbuffer2,TexCoord).xyz;
//////////////////////////////

//////////////////////////////
color=vec4(texture2D(gbuffer0,TexCoord))*Brightness;
}