#include "Include/computeshader.h"
ComputeShader::ComputeShader(const char *file)
 :Program((GLuint)0)
{
    Shader shader(file,GL_COMPUTE_SHADER);
    id=api->glCreateProgram();
    api->glAttachShader(id,shader.getid());
    api->glLinkProgram(id);
    Program::geterror(id);
}

ComputeShader::ComputeShader(const char *code, bool reserve)
:Program((GLuint)0)
{
    Shader shader(code,GL_COMPUTE_SHADER,1);
    id=api->glCreateProgram();
    api->glAttachShader(id,shader.getid());
    api->glLinkProgram(id);
    Program::geterror(id);
}

void ComputeShader::run(GLuint group_x, GLuint group_y, GLuint group_z)
{
    api->glDispatchCompute(group_x,group_y,group_z);
}

void ComputeShader::barrierImage()
{
    api->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeShader::barrierSsbo()
{
api->glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

uvec3 ComputeShader::getMaxGroupSize()
{

    static bool init=0;
    static uvec3 size;
    if(!init)
    {
        init=1;
        for(int i=0;i<3;++i)
            api->glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,i,(int*)&size[i]);
    }
    return size;
}

uvec3 ComputeShader::getMaxGroupCount()
{
    static bool init=0;
    static uvec3 count;
    if(!init)
    {
        init=1;
        for(int i=0;i<3;++i)
            api->glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT,i,(int*)&count[i]);
    }
    return count;
}

Uint ComputeShader::getMaxInvocations()
{
    static bool init=0;
    static Uint nums;
    if(!init)
    {
        init=1;
        api->glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,(int*)&nums);
    }
    return nums;
}

ComputeShader::~ComputeShader()
{

}
