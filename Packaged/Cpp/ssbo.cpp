#include "Include/ssbo.h"
Ssbo::Ssbo(GLuint size, void *data)
:BufferBase<GL_SHADER_STORAGE_BUFFER>(size,data)
{

}

void Ssbo::bind_range(GLuint offset_begin, GLuint bind_size, GLuint index)
{
     api->glBindBufferRange(GL_SHADER_STORAGE_BUFFER,index,id,offset_begin,bind_size);
}

void Ssbo::bind_base(GLuint index)
{
    api->glBindBufferBase(GL_SHADER_STORAGE_BUFFER,index,id);
}

Ssbo::~Ssbo()
{

}
