#include "Include/ebo.h"


Ebo::Ebo(GLuint size, GLuint *data):BufferBase<GL_ELEMENT_ARRAY_BUFFER>(size*sizeof(GLuint),data)
{

}

void Ebo::setdata(GLuint size, GLuint offset, GLuint *data)
{
    BufferBase<GL_ELEMENT_ARRAY_BUFFER>::setdata(
         sizeof(GLuint) * size, sizeof(GLuint) * offset, (void *)data);
}

void Ebo::setdata(GLuint size, GLuint *data) { setdata(size, 0, data); }

Ebo::~Ebo()
{

}
