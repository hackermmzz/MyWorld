#version 460 core
layout(Triangles)in;
layout(triangle_strip,max_vertices=3)out;
uniform mat4 view[6];
in int Layer[];
out vec3 FragPos;
void main()
{
for(int i=0;i<5;++i)
{
gl_Layer=Layer[0];
for(int ii=0;ii<3;++ii)
{
vec3 pos=gl_in[ii].gl_Position.xyz;
vec4 PosToView=view[gl_Layer]*vec4(pos,1.0);
gl_Position=PosToView.xyww;
FragPos=pos;
EmitVertex();
}
EndPrimitive();
}
}