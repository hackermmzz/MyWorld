#ifndef COMPUTESHADER_H
#define COMPUTESHADER_H
#include"program.h"
class ComputeShader:public Program
{
public:
    ComputeShader(const char*file);
    ComputeShader(const char*code,bool reserve);
    void run(GLuint group_x,GLuint group_y,GLuint group_z);
    void barrierImage();
    void barrierSsbo();
    static uvec3 getMaxGroupSize();
    static uvec3 getMaxGroupCount();
    static Uint getMaxInvocations();
    ~ComputeShader();
};

#endif // COMPUTESHADER_H
