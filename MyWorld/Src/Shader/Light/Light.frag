#version 460 core
uniform sampler2D screen;
uniform sampler2D Position;
uniform sampler2D Normal;
uniform int LightNums;
uniform float Brightness;
struct PointLight{
    vec4 position;
    vec4 color;
};
layout(std430)buffer LIGHTS{
PointLight lights[];
};
in vec2 TexCoord;
out vec4 color;
const float PointLightInfluenceArea=5.0;
const float DisThreold=sqrt(3)/2;
vec3 ProcessPointLight(vec3 color,vec3 pos,vec3 normal,float dis,PointLight light){
float fac=1/(dis*dis);
if(dis<DisThreold)return light.color.rgb*color*fac;
else{
vec3 vec=light.position.xyz-pos;
float theta=dot(vec,normal);
if(theta>=0)return  light.color.rgb*color*fac;
return vec3(0);
}
}
void main()
{
vec3 BaseColor=texture2D(screen,TexCoord).rgb;
vec3 normal=texture2D(Normal,TexCoord).xyz;
vec3 position=texture2D(Position,TexCoord).xyz;
/////////////////////////////////////////////////
/////////////////////////////////////////////////
float dis;
vec3 pointLightColor=vec3(0.0);
for(int i=0;i<LightNums;++i)
{
dis=length(lights[i].position.xyz-position);
if(dis<=PointLightInfluenceArea)
pointLightColor+=ProcessPointLight(BaseColor,position,normal,dis,lights[i]);
}
color=vec4(BaseColor*Brightness+pointLightColor,1.0);
}