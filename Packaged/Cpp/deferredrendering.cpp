#include "Include/deferredrendering.h"
DeferredRendering::DeferredRendering(GLuint width,GLuint height,const vector<GLenum>&types)
    :Fbo()
{
    buffer_width = width, buffer_height = height;
    GLuint buffer_nums=types.size();
    rbo=new Rbo(width,height);
    attachRbo(*rbo);
    buffers.resize(buffer_nums);
    GLenum attachment=GL_COLOR_ATTACHMENT0;
    vector<GLenum>attachment_types(buffer_nums);
    for(unsigned int i=0;i<buffer_nums;++i)
    {
        auto&buffer=buffers[i];
        buffer=new Texture2DGeneral(width,height,types[i],GL_RGBA,GL_FLOAT,0);
        buffer->wrap(GL_CLAMP_TO_EDGE);
        buffer->filter(GL_NEAREST);
        attachTexture(*buffer,attachment+i);
        attachment_types[i]=attachment+i;
    }
    setDrawBuffers(buffer_nums,attachment_types.data());
}

void DeferredRendering::bind()
{
    Fbo::bind();
    buffers[0]->fitViewport();
    api->glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

void DeferredRendering::apply(Program &program)
{
    /////////////////////初始化
    static bool init=0;
    static std::string *buffer_name;
    if(!init)
    {
        init=1;
        GLint size;
        api->glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&size);
        buffer_name=new std::string[size];
        for(int i=0;i<size;++i)buffer_name[i]=DEFERREDRENDRING_BUFFER_NAME+std::to_string(i);
    }
    ////////////////////
    auto size=buffers.size();
    for(unsigned int i=0;i<size;++i)
    {
        program.setint(buffer_name[i].c_str(),i);
        buffers[i]->bind(i);
    }
}

vector<Texture2DGeneral*>& DeferredRendering::GetBuffers()
{
    return buffers;
}

Uint DeferredRendering::GetBufferWidth()
{
    return buffer_width;
}

Uint DeferredRendering::GetBufferHeight()
{
    return buffer_height;
}


DeferredRendering::~DeferredRendering()
{
    if(rbo)delete rbo;
    for(auto*buffer:buffers)delete buffer;
}
