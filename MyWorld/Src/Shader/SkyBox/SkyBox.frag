#version 460 core
precision highp float;
in vec3 TexCoords;
uniform samplerCube sampler;
out vec4 color;
void main(){
color=texture(sampler,TexCoords);
}