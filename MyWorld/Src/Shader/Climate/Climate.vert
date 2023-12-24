#version 460 core
layout(location=0)in vec4 data;
out int Layer;
void main(){
Layer=int(data.w);
gl_Position = vec4(data.xyz, 1.0);
}