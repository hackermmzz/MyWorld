#ifndef UBO_H
#define UBO_H
#include"Include.h"
#include"BufferBase.hpp"
class Ubo:public BufferBase<GL_UNIFORM_BUFFER>
{
private:
public:
    Ubo(GLuint buffer_size,void*data=0);
    void bind_range(GLuint offset_begin,GLuint bind_size,GLuint index=0);
    void bind_base(GLuint index);
    ~Ubo();
};

#endif // UBO_H
