#version 460 core
layout(triangles)in;
layout(triangle_strip,max_vertices=3)out;
out vec2 TexCoord;
void main()
{
for(int i=0;i<3;++i)
{
gl_Layer=2;
TexCoord=gl_in[i].gl_Position.xy;
gl_Position=gl_in[i].gl_Position;
EmitVertex();
}
EndPrimitive();
}