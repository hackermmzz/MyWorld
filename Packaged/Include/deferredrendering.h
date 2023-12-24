#ifndef DEFERREDRENDERING_H
#define DEFERREDRENDERING_H
#include"fbo.h"
#include<vector>
#include"program.h"
using std::vector;
////////////////////
class DeferredRendering:public Fbo
{
private:
    Rbo*rbo;
    vector<Texture2DGeneral*>buffers;
    Uint buffer_width, buffer_height;
public:
    DeferredRendering(GLuint width,GLuint height,const vector<GLenum>&types);
    void bind();
    void apply(Program&program);
    vector<Texture2DGeneral*>& GetBuffers();
    Uint GetBufferWidth();
    Uint GetBufferHeight();
    ~DeferredRendering();
};

#endif // DEFERREDRENDERING_H
