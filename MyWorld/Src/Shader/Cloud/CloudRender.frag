#version 460 core
uniform sampler2D cloud;
in vec2 TexCoord;
in vec2 FragPos;
out vec4 color;
void main()
{
float value=texture2D(cloud,TexCoord).r;
float height=sqrt(1.0-FragPos.x*FragPos.x-FragPos.y*FragPos.y);
vec2 EdgeDis=TexCoord-vec2(0.5);
float weight=max(abs(EdgeDis.x),abs(EdgeDis.y))*2;
float alpha=smoothstep(value,0,1-height);
/////////////////////////////
////////////////////////////
vec3 baseColor=mix(vec3(0.0,0.8,1.0),vec3(1.0),value);
color=vec4(baseColor,1.0);
}