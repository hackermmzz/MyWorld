#version 460 core
uniform sampler2D screen;
uniform bool horizon;
in vec2 TexCoord;
out vec4 color;
float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
vec3 result=texture2D(screen,TexCoord).rgb*weight[0];
ivec2 size=textureSize(screen,0);
if(horizon)
{
for(int i=1;i<5;++i)
{
float xOffset=i/size.x;
result+=texture2D(screen,vec2(TexCoord.x+xOffset,TexCoord.y)).rgb*weight[i];
result+=texture2D(screen,vec2(TexCoord.x-xOffset,TexCoord.y)).rgb*weight[i];
}
}
else{
for(int i=1;i<5;++i)
{
float yOffset=i/size.y;
result+=texture2D(screen,vec2(TexCoord.x,TexCoord.y+yOffset)).rgb*weight[i];
result+=texture2D(screen,vec2(TexCoord.x,TexCoord.y-yOffset)).rgb*weight[i];
}
}
color=vec4(result,1.0);
}