#include "Include/mesh.h"
Mesh::Mesh(Mesh &&mesh)
{
    texture=mesh.texture;
    vao=mesh.vao;
    vbo=mesh.vbo;
    ebo=mesh.ebo;
    ShadowRenderVao=mesh.ShadowRenderVao;
    indices_size=mesh.indices_size;
    step_size=mesh.step_size;
    mesh.vao=0,mesh.vbo=0,mesh.ebo=0,mesh.ShadowRenderVao=0;
}

Mesh::Mesh(vector<Vertex> &vertex, vector<GLuint> &indices, vector<Texture>&textures,size_t mask)
{
    indices_size=indices.size();
    texture=textures;
    ShadowRenderVao=0;
    step_size=0;
    ////////设置vao,vbo,ebo
    vao=new Vao;
    ////////////////////////////
    bool state[6];
    for(int i=0;i<6;++i)state[i]=mask&(1<<i);
    ///////获得传入着色器的vertex大小
    if(state[0])step_size+=sizeof(Vertex::Position);
    if(state[1])step_size+=sizeof(Vertex::Normal);
    if(state[2])step_size+=sizeof(Vertex::Texcoord);
    if(state[3])step_size+=sizeof(Vertex::Tangent);
    if(state[4])step_size+=sizeof(Vertex::Bitangent);
    if(state[5])step_size+=sizeof(Vertex::BoneID)+ sizeof(Vertex::Weight);
    vbo=new Vbo(vertex.size()*step_size);
    byte*ptr=(byte*)vbo->map(vertex.size()*step_size,0,GL_MAP_WRITE_BIT);
    /////////////传入数据
    unsigned int offset_=0;
    for(auto&data:vertex)
    {
        if(state[0])
        {
            *(vec3*)(ptr+offset_)=data.Position;
            offset_+=sizeof(vec3);
        }
        if(state[1])
        {
            *(vec3*)(ptr+offset_)=data.Normal;
           offset_+=sizeof(vec3);
        }
        if(state[2])
        {
           *(vec2*)(ptr+offset_)=data.Texcoord;
           offset_+=sizeof(vec2);
        }
        if(state[3])
        {
           *(vec3*)(ptr+offset_)=data.Tangent;
           offset_+=sizeof(vec3);
        }
        if(state[4])
        {
           *(vec3*)(ptr+offset_)=data.Bitangent;
           offset_+=sizeof(vec3);
        }
        if(state[5])
        {
           *(BoneIdType*)(ptr+offset_)=data.BoneID;
           offset_+=sizeof(BoneIdType);
           *(WeightType*)(ptr+offset_)=data.Weight;
           offset_+=sizeof(WeightType);
        }
    }
    ////////////////////////////设置顶点属性
    unsigned  int n = 0;
    unsigned int offset = 0;
    if(state[0])
    {
    vbo->setpoint(n++,GL_FLOAT,3,step_size,offset);
    offset+=sizeof(vec3);
    }
    if(state[1])
    {
    vbo->setpoint(n++,GL_FLOAT,3,step_size,offset);
    offset+=sizeof(vec3);
    }
    if(state[2]){
    vbo->setpoint(n++,GL_FLOAT,2,step_size,offset);
    offset+=sizeof(vec2);
    }
    if(state[3])
    {
    vbo->setpoint(n++,GL_FLOAT,3,step_size,offset);
    offset+=sizeof(vec3);
    }
    if(state[4])
    {
    vbo->setpoint(n++,GL_FLOAT,3,step_size,offset);
    offset+=sizeof(vec3);
    }
    if(state[5])
    {
    vbo->setpointiv(n++,GL_INT,MODEL_MAX_BONES_INFLUENCE,step_size,offset);
    offset+=sizeof(BoneIdType);
    vbo->setpoint(n++,GL_FLOAT,MODEL_MAX_BONES_INFLUENCE,step_size,offset);
    offset+=sizeof(WeightType);
    }
    //////////////
    vbo->unmap();
     ebo=new Ebo(indices.size(),indices.data());
    vao->unbind();
    ////////
}

void Mesh::Draw(Program &program,GLuint instance)
{
    ////////////////////初始化
    static bool init=0;
    static string*diffuse_name;
    static string* specular_name;
    static string* normal_name;
    static string* height_name;
    static string* ambient_name;
    if(!init)
    {
    init=1;
    GLint size;
    api->glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&size);
    diffuse_name=new string[size];
    specular_name=new string[size];
    normal_name=new string[size];
    height_name=new string[size];
    ambient_name=new string[size];
    for(int i=0;i<size;++i)
    {
     string i_str=to_string(i);
     diffuse_name[i]=TEXTURE_AMBIENT+i_str;
     specular_name[i]=TEXTURE_SPECULAR+i_str;
     normal_name[i]=TEXTURE_NORMAL+i_str;
     height_name[i]=TEXTURE_HEIGHT+i_str;
     ambient_name[i]=TEXTURE_AMBIENT+i_str;
    }
    }
    ///////////////////
    unsigned int diffuse = 0;
    unsigned int specular = 0;
    unsigned int normal=0;
    unsigned int height=0;
    unsigned int ambient=0;
    for(unsigned int i = 0; i < texture.size(); i++)
    {
        api->glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        // 获取纹理序号（diffuse_textureN 中的 N）
        string*str;
        TextureType type = texture[i].type;
         if(type==AMBIENT)
        str=&ambient_name[ambient++];
        else if(type== DIFFUSE)
        str =&diffuse_name[diffuse++];
        else if(type == SPECULAR)
        str=&specular_name[specular++];
        else if(type==NORMAL)
        str=&normal_name[normal++];
        else if(type==HEIGHT)
        str=&height_name[height++];
        program.setint(str->c_str(),i);
        api->glBindTexture(GL_TEXTURE_2D, texture[i].id);
    }
    // 绘制网格
    vao->bind();
    ///////////////////判断是否实例化绘制
    if(instance)
    api->glDrawElementsInstanced(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0,instance);
    else
    api->glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
}

void Mesh::DrawShadow(GLuint instance)
{
    if(ShadowRenderVao==0)
    {
    ShadowRenderVao=new Vao();
    ///////////////////////
    vbo->bind();
    vbo->setpoint(0,GL_FLOAT,3,step_size,0);
    ebo->bind();
    ///////////////////////
    ShadowRenderVao->unbind();
    }
    ShadowRenderVao->bind();
    if(instance)
    api->glDrawElementsInstanced(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0,instance);
    else
    api->glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
}

Vao*Mesh::getVao()
{
    return vao;
}

Vao *Mesh::getShadowRenderVao()
{
    return ShadowRenderVao;
}

Vbo*Mesh::getVbo()
{
    return vbo;
}

Ebo*Mesh::getEbo()
{
    return ebo;
}
Mesh::~Mesh()
{
    if(vao)delete vao;
    if(vbo)delete vbo;
    if(ebo)delete ebo;
    if(ShadowRenderVao)delete ShadowRenderVao;
}
