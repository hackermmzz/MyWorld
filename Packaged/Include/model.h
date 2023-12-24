#ifndef MODEL_H
#define MODEL_H
#include"mesh.h"
#include"Include.h"
#include<unordered_map>
#include<string.h>
using  std::string;
using std::unordered_map;
//////////////////////////////////////////////assimp库
#include"assimp/Importer.hpp""
#include"assimp/scene.h"
#include"assimp/postprocess.h"
using namespace Assimp;
//////////////////////////////////////////
struct BoneInfo
{
    GLuint id;
    Matrix BoneSpace;
};
//////////////////////////////////////////
class Model
{
  private:
    vector<Mesh>mesh;
    size_t input_mask;//传入的着色器的vertex成员
    string model_path;//模型的路径
    vector<GLuint>loaded_texture;//所有已加载的纹理id
    unordered_map<string,Texture>texture_map;//记录所有已加载的纹理
    GLuint bones_count;//记录骨头当前的数量
    unordered_map<string,BoneInfo>bone_map;//记录所有骨头消息
    ////////////////////////////遍历aiscene节点
    void ProcessNode(const aiScene*scene,aiNode*node);
    ///////////////////////////处理mesh转换为我定义的mesh数据
    Mesh ProcessMesh(const aiScene*scene,aiMesh*mesh);
    /////////////////////
    vector<Texture> LoadMaterialTextures(aiMaterial*mat,aiTextureType type,TextureType type_);
    //////////////////////
    void LoadBones(vector<Vertex>&vertex,aiMesh*mesh);
public:
    Model(const char*filesize_t,size_t input_mask=MODEL_ALL,size_t process_mask = MODEL_DEFAULT_PROCESS_MASK);
    void Draw(Program&program,GLuint instance=0);
    void DrawShadow(GLuint instance=0);
    GLuint& getBoneNums();
    unordered_map<string,BoneInfo>& getBoneMap();
    vector<Mesh>&getMesh();
    ~Model();
};

#endif // MODEL_H
