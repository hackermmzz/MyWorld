#ifndef VAO_H
#define VAO_H
#include"Include.h"
class Vao
{
private:
    GLuint id;
public:
    Vao();
    void bind();
    void unbind();
    GLuint getid();
    ~Vao();
};
#endif // VAO_H
