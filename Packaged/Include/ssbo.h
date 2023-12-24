#ifndef SSBO_H
#define SSBO_H
#include"BufferBase.hpp"
class Ssbo:public BufferBase<GL_SHADER_STORAGE_BUFFER>
{

public:
    Ssbo(GLuint size,void*data=0);
    void bind_range(GLuint offset_begin,GLuint bind_size,GLuint index=0);
    void bind_base(GLuint index);
    ~Ssbo();
};

#endif // SSBO_H
