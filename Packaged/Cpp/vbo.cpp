#include "Include/vbo.h"

Vbo::Vbo(GLuint size, void *data):BufferBase<GL_ARRAY_BUFFER>(size,data)
{

}

void Vbo::setpoint(GLuint location, GLenum value_type, GLuint num, GLuint step_size, GLuint offset)
{
    api->glEnableVertexAttribArray(location);
    api->glVertexAttribPointer(location, num, value_type, GL_FALSE, step_size,(void*)(offset));
}

void Vbo::setpointiv(GLuint location, GLenum value_type, GLuint num, GLuint step_size, GLuint offset)
{
    api->glEnableVertexAttribArray(location);
    api->glVertexAttribIPointer(location, num, value_type,step_size,(void*)(offset));
}

void Vbo::setpoint(GLuint location, GLuint divisor)
{
   api->glEnableVertexAttribArray(location);
    api->glVertexAttribDivisor(location, divisor);
}

void Vbo::disablepoint(GLuint location)
{
    api->glDisableVertexAttribArray(location);
}
Vbo::~Vbo() {}
