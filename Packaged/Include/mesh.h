#ifndef MERSH_H
#define MERSH_H
#include"Include.h"
#include<vector>
#include"vec.hpp"
#include"texture2d.h"
#include<string>
#include<iostream>
#include"vao.h"
#include"vbo.h"
#include"ebo.h"
#include"program.h"
//////////////////////////////////////////////
using  std::vector;
using  std::string;
using  std::to_string;
//////////////////////////
enum TextureType{AMBIENT,DIFFUSE,SPECULAR,HEIGHT,NORMAL};
//////////////////////////
using BoneIdType=ivec<MODEL_MAX_BONES_INFLUENCE>;
using WeightType=vec<MODEL_MAX_BONES_INFLUENCE>;
//////////////////////////
struct Vertex{
   vec3 Position;
   vec3 Normal;
   vec2 Texcoord;
   vec3 Tangent;
   vec3 Bitangent;
   BoneIdType BoneID;
   WeightType Weight;
};
///////
struct Texture{
    GLuint id;
   TextureType type;
};
/////////
enum InputType
{
    VERTEX_POSITION=1,
    VERTEX_NORMAL=2,
    VERTEX_TEXCOORD=4,
    VERTEX_TANGENT=8,
    VERTEX_BITANGENT=16,
    VERTEX_BONEID_WEIGHT=32,
    MODEL_BASE=VERTEX_POSITION|VERTEX_NORMAL|VERTEX_TEXCOORD,
    MODEL_ALL=MODEL_BASE|VERTEX_TANGENT|VERTEX_BITANGENT,
    ANIMATION_ALL=MODEL_ALL|VERTEX_BONEID_WEIGHT
};
/////////
class Mesh
{
private:
   GLuint indices_size;
    vector<Texture>texture;
    Vao*vao;
    Vbo*vbo;
    Ebo*ebo;
    ///////////////////////
    Vao*ShadowRenderVao;
    GLuint step_size;
    //////////////////////////////
public:
    Mesh(vector<Vertex>&vertex,vector<GLuint>&indices,vector<Texture>&textures,size_t mask);
    Mesh(Mesh&&mesh);
    void Draw(Program&program,GLuint instance=0);
    void DrawShadow(GLuint instance=0);
    Vao*getVao();
    Vao*getShadowRenderVao();
    Vbo *getVbo();
    Ebo*getEbo();
    ~Mesh();
};

#endif // MERSH_H
