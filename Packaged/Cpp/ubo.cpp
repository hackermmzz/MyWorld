#include "Include/ubo.h"
Ubo::Ubo(GLuint buffer_size,void*data):BufferBase<GL_UNIFORM_BUFFER>(buffer_size,data){}

void Ubo::bind_range(GLuint offset_begin, GLuint bind_size, GLuint index)
{
    api->glBindBufferRange(GL_UNIFORM_BUFFER,index,id,offset_begin,bind_size);
}

void Ubo::bind_base(GLuint index)
{
    api->glBindBufferBase(GL_UNIFORM_BUFFER,index,id);
}

Ubo::~Ubo()
{

}
