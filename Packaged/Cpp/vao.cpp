#include"Include/vao.h"
Vao::Vao()
{
    api->glGenVertexArrays(1,&id);
    bind();
}

void Vao::bind()
{
   api->glBindVertexArray(id);
}

void Vao::unbind()
{
    api->glBindVertexArray(0);
}

GLuint Vao::getid()
{
    return id;
}

Vao::~Vao()
{
    if(id)
        api->glDeleteVertexArrays(1,&id);
}
