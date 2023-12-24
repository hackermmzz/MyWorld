#version 460 core
in vec3 FragPos;
out vec4 color;
uniform sampler2D cloud;
uniform sampler2D star;
uniform vec3 LightPos;
uniform vec3 Light;
uniform float Brightness;
uniform float StarBrightness;
const float Theta=0.999;
const vec3 skyColor=vec3(0.0,0.75,1.0);
const float exposure=5.0;
vec4 GetCloudColor(vec2 uv)
{
vec2 EdgeDis=uv-vec2(0.5);
float weight=max(abs(EdgeDis.x),abs(EdgeDis.y))*2;
float value=texture2D(cloud,uv).r;
float alpha=smoothstep(value,0,weight);
return vec4(vec3(value),alpha);
}
vec3 GetStarColor(vec2 uv)
{
vec3  color=texture2D(star,uv).rgb;
return color;
}
vec3 ProcessCloud(vec3 color)
{
color=vec3(1.0)-exp(-color*exposure);
return color;
}
void main()
{
vec3 pos=normalize(FragPos);
float theta=dot(pos,LightPos);
vec2 uv=FragPos.xz*0.5+0.5;
if(pos.y>0&&theta>=Theta)
{
float smoothstepValue=smoothstep(0.0,1.0,(theta-Theta)/(1-Theta));
float brightness =mix(0.8,1.0,smoothstepValue);
vec3 SunColor=vec3(Light)*brightness;
color=vec4(SunColor,1.0);
return;
}
vec3 skycolor=skyColor*Brightness;
bool Check=FragPos.y==1.0;
vec4 cloudColor=Check?GetCloudColor(uv):vec4(0.0);
if(cloudColor.a!=0.0)
{
color=vec4(mix(skycolor,ProcessCloud(cloudColor.rgb),cloudColor.a),1.0)*Brightness;
return;
}
else{
if(LightPos.y<=0){
vec3 starcolor=Check?GetStarColor(uv):vec3(0.0);
starcolor*=StarBrightness;
if(starcolor.b!=0.0)
{
color=vec4(starcolor,1.0);
return;
}
}
color=vec4(skycolor,1.0);
}
}