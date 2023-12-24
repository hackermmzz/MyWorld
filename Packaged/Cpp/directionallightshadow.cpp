#include "Include/directionallightshadow.h"
DirectionalLightShadow::DirectionalLightShadow(const vec3 &direction, GLuint width_, GLuint height_, GLuint level, Matrix &projection, Matrix &view, const vec<10> &percentage, float MulFactor)
    :DirectionalLightShadow(direction,width_,height_,level)
{
    update(projection,view,percentage,MulFactor);
}

DirectionalLightShadow::DirectionalLightShadow(const vec3&direction, GLuint width_, GLuint height_,GLuint level)
    :ShadowBase(DIRECTIONALLIGHTSHADOW,direction,&width_,&height_,level)
{
    position=direction;
    levels=level;
    vp=new Matrix[level];
}

void DirectionalLightShadow::bind()
{
    static bool init=0;
    if(!init)
    {
        init=1;
        //////////////////////////////
        const char*vertex="#version 420 core\n"
                             "layout(location=0)in vec3 pos;\n"
                             "uniform mat4 model;\n"
                             "void main(void)\n"
                             "{\n"
                             "    gl_Position =model*vec4(pos,1.0);\n"
                             "}\n";
        std::string levels_str=std::to_string(levels);
        std::string gemo="#version 420 core\n"
                           "layout(triangles, invocations ="+levels_str+")in;\n"
                           "layout(triangle_strip, max_vertices = 3) out;\n"
                           "uniform mat4 vp["+levels_str+"];\n"
                           "void main()\n"
                           "{\n"
                           "        for (int i = 0; i < 3; ++i)\n"
                           "        {\n"
                           "                gl_Position = vp[gl_InvocationID] * gl_in[i].gl_Position;\n"
                           "                gl_Layer = gl_InvocationID;\n"
                           "                EmitVertex();\n"
                           "        }\n"
                           "        EndPrimitive();\n"
                            "}\n";
        const char*frag="#version 420 core\n"
                           " void main()\n"
                           "{}";
        program=new Program(vertex,gemo.c_str(),frag,1);
        //////////////////////////////
    }
    ShadowBase::bind();
    for(int i=0;i<levels;++i)
    program->setmat4(("vp["+std::to_string(i)+"]").c_str(),vp[i]);
}

GLuint DirectionalLightShadow::getLevel()
{
    return levels;
}

Matrix *DirectionalLightShadow::getVpMatrix()
{
    return vp;
}

void DirectionalLightShadow::setDirection(const vec3 &dir)
{
    setPosition(dir);
}
void DirectionalLightShadow::update(Matrix &vp_, const vec<DIRECTIONALLIGHTSHADOW_MAX_LEVEL> &percentage,float MulFactor)
{
  Matrix vp_inverse=vp_.inverse();
    static vec3 store[8];
    ////////////////////////////////
    unsigned int count_=0;
    for( int x=0;x<2;++x)
    {
        for(int y=0;y<2;++y)
        {
            for(int z=0;z<2;++z)
            {
                vec4 pos_vp=vp_inverse*vec4(2*x-1,2*y-1,2*z-1,1.0);
                store[count_++]=vec3{pos_vp}/pos_vp[3];
            }
        }
    }
    ///////////////////////////////////获取各个截面的四个点坐标
    static Vec<vec3,4>face[DIRECTIONALLIGHTSHADOW_MAX_LEVEL+1];
    face[0]={store[0],store[4],store[6],store[2]};//near
    face[levels]={store[1],store[5],store[7],store[3]};//far
    vec3 v1=store[1]-store[0];
    vec3 v2=store[5]-store[4];
    vec3 v3=store[7]-store[6];
    vec3 v4=store[3]-store[2];
    for(int i=1;i<levels;++i)
    {
    auto&face_=face[i];
    double percent=percentage.get(i-1);
    face_[0]=store[0]+v1*percent;
    face_[1]=store[4]+v2*percent;
    face_[2]=store[6]+v3*percent;
    face_[3]=store[2]+v4*percent;
    }
    /////////////////////////////////产生正交透视矩阵
    double temp[6];//存储坐标各个维度的极值
    for(int i=0;i<levels;++i){
        for(int i=0;i<3;++i)//初始化temp
        {
            temp[i*2]=FLT_MAX;
            temp[i*2+1]=FLT_MIN;
        }
        ///////////////////////获得视锥中心
        vec3 center{0,0,0};
        for(int ii=0;ii<8;++ii)
            center+=face[i+ii/4][ii%4];
        center/=8.0;
        Matrix view=Matrix::camera(center+position,center,{0,1,0});
        for(int iii=0;iii<8;++iii)
        {
           vec3 corner=face[i+iii/4][iii%4];
           corner=vec3{view*vec4{corner[0],corner[1],corner[2],1.0f}};
            temp[0]=fmin(temp[0],corner[0]);
            temp[1]=fmax(temp[1],corner[0]);
            temp[2]=fmin(temp[2],corner[1]);
            temp[3]=fmax(temp[3],corner[1]);
            temp[4]=fmin(temp[4],corner[2]);
            temp[5]=fmax(temp[5],corner[2]);
           }
    /////////////////////////////////////////放缩包围盒的z轴
       temp[4]=temp[4]>=0?temp[4]/MulFactor:temp[4]*MulFactor;
       temp[5]=temp[5]>=0?temp[5]*MulFactor:temp[5]/MulFactor;
    /////////////////////////////////////////生成矩阵
    Matrix projection=Matrix::ortho(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
    vp[i]=projection*view;
    }

}
void DirectionalLightShadow::update(Matrix &projection, Matrix &view, const vec<DIRECTIONALLIGHTSHADOW_MAX_LEVEL> &percentage,float MulFactor)
{
    Matrix vp_=projection*view;
    update(vp_,percentage,MulFactor);
}
DirectionalLightShadow::~DirectionalLightShadow()
{
    if(vp)delete []vp;
}

