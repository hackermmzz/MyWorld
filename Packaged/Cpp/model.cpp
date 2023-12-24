#include "Include/model.h"
void Model::ProcessNode(const aiScene *scene, aiNode *node)
{
    for(unsigned int i=0;i<node->mNumMeshes;++i)
    {
        auto*mesh_=scene->mMeshes[node->mMeshes[i]];
        mesh.push_back(ProcessMesh(scene,mesh_));
    }
    for(unsigned int i=0;i<node->mNumChildren;++i)
    {
        ProcessNode(scene,node->mChildren[i]);
    }
}

Mesh Model::ProcessMesh(const aiScene *scene, aiMesh *mesh_)
{

    vector<Vertex>vertex;
    vector<GLuint>indices;
    vector<Texture>textures;
    /////////////////////////////////判断是否读取
    bool state[6];
    for(GLuint i=0;i<6;++i)
     state[i]=input_mask&(1<<i);
     /////////////////////////////////加载顶点信息
    for(unsigned int i=0;i<mesh_->mNumVertices;++i)
    {
        Vertex temp;
        ////////////////初始化temp
        temp.BoneID=BoneIdType{-1};
        temp.Weight=WeightType{0.0};
        ////////////////加载坐标
        if(state[0]){
        auto&vertex_data=mesh_->mVertices[i];
        temp.Position={vertex_data.x,vertex_data.y,vertex_data.z};
        }
        ////////////////加载法线
        if(state[1]){
           auto&normal_data=mesh_->mNormals[i];
           temp.Normal={normal_data.x,normal_data.y,normal_data.z};
        }
        //////////////////加载纹理坐标
        if(state[2]&&mesh_->mTextureCoords[0])
        {

            auto&coords_data=mesh_->mTextureCoords[0][i];
            temp.Texcoord={coords_data.x,coords_data.y};
        }
        /////////////加载主切线和副切线
        if((state[3]||state[4])&&mesh_->HasTangentsAndBitangents()){
         ////tangent
            if(state[3]){
        auto&tangent_=mesh_->mTangents[i];
        temp.Tangent={tangent_.x,tangent_.y,tangent_.z};
            }
         //////bitangent
        if(state[4]){
        auto&bitangent_=mesh_->mBitangents[i];
        temp.Bitangent={bitangent_.x,bitangent_.y,bitangent_.z};
            }
        }
        vertex.push_back(temp);
    }
    ///////////////////////////////////加载索引信息
    for(unsigned int i=0;i<mesh_->mNumFaces;++i)
    {
        auto&face=mesh_->mFaces[i];
        for(unsigned int t=0;t<face.mNumIndices;++t)
        indices.push_back(face.mIndices[t]);
    }
    ///////////////////////////////////加载材质信息
    if(mesh_->mMaterialIndex>=0){
    auto*material=scene->mMaterials[mesh_->mMaterialIndex];
    ////////////////////////////加载纹理
    // 1. diffuse maps
    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE,DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, NORMAL);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT,HEIGHT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    //5. ambient maps
    std::vector<Texture> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT,AMBIENT);
    textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
    }
    //////////////////////////////////////加载骨头
    if(state[5])
     LoadBones(vertex,mesh_);
    //////////////////////////////////////
    return Mesh(vertex, indices, textures,input_mask);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType type_)
{
    vector<Texture>texture;
    for(unsigned int i=0;i<mat->GetTextureCount(type);++i)
    {
        aiString str;
        mat->GetTexture(type,i,&str);
        string strr=str.C_Str();
        bool skip=(texture_map.find(strr)!=texture_map.end());
        if(skip)
        texture.push_back(texture_map[strr]);
        else {
        Texture2D temp(string(model_path+string("/")+str.C_Str()).c_str());
        Texture temp_;
        temp_.id=temp.preserve();
        temp_.type=type_;
        texture_map[strr.c_str()]=temp_;
        loaded_texture.push_back(temp_.id);
        texture.push_back(temp_);
        }
    }
    return texture;
}

void Model::LoadBones(vector<Vertex> &vertex, aiMesh *mesh)
{
    GLuint bone_nums=mesh->mNumBones;
    for(GLuint i=0;i<bone_nums;++i)
    {
        auto*bone=mesh->mBones[i];
        GLuint id=-1;
        string name=string(bone->mName.C_Str());
        auto itr = bone_map.find(name);
        if(itr==bone_map.end())
        {
        BoneInfo info;
        id=bones_count++;
        info.id=id;
        info.BoneSpace=Matrix::ConvertToColumnFormat(&bone->mOffsetMatrix.a1);
        bone_map[name]=info;
        }
        else{
        id=itr->second.id;
        }
        ////////////////////加载权重
        auto*weights=bone->mWeights;
        for(Uint i=0;i<bone->mNumWeights;++i)
        {
        GLuint vertexid=weights[i].mVertexId;
        auto val=weights[i].mWeight;
        auto&vertex_=vertex[vertexid];
        for(int i=0;i<MODEL_MAX_BONES_INFLUENCE;++i)
        {
        if(vertex_.BoneID[i]<0)
        {
            vertex_.BoneID[i]=id;
            vertex_.Weight[i]=val;
            break;
        }
        }
        }
        ////////////////////
    }
}

Model::Model(const char *file,size_t input_mask_, size_t process_mask)
{
    bones_count=0;
    input_mask=input_mask_;
    model_path=file;
    int n=model_path.find_last_of("/");
    model_path=model_path.substr(0,n);
    Importer impoter;
    auto*scene=impoter.ReadFile(file,process_mask);
    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode)
    {
       std::cout<<impoter.GetErrorString()<<std::endl;
        return;
    }
   ProcessNode(scene,scene->mRootNode);
}


void Model::Draw(Program &program,GLuint instance)
{
    for(auto&mesh_:mesh)
        mesh_.Draw(program,instance);
}

void Model::DrawShadow( GLuint instance)
{
    for(auto&mesh_:mesh)
        mesh_.DrawShadow(instance);
}

GLuint& Model::getBoneNums()
{
    return bones_count;
}

unordered_map<string, BoneInfo> &Model::getBoneMap()
{
    return bone_map;
}

vector<Mesh>& Model::getMesh()
{
    return mesh;
}

Model::~Model()
{
    if(loaded_texture.size())
        api->glDeleteTextures(loaded_texture.size(),&loaded_texture[0]);
}
