#ifndef EBO_H
#define EBO_H
#include"BufferBase.hpp"
class Ebo:public BufferBase<GL_ELEMENT_ARRAY_BUFFER>
{
public:
    Ebo(GLuint size, GLuint *data = 0);
     void setdata(GLuint size, GLuint offset, GLuint *data);
    void setdata(GLuint size, GLuint *data);
    ~Ebo();
};

#endif // EBO_H
