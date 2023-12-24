#ifndef SECTION_H
#define SECTION_H
#include"globalsource.h"
struct Section
{
    void*Chunk;//所属的chunk
    int id;//标志section,最底下那一个section的id为0
    ivec3 position;//左下角位置
    Vao*vao;
    static Ebo*ebo;
    Vbo*block_render;//存储一个区块中将被渲染的实体方块的面
    vector<Face>face;//将被渲染实体方块的面
    Vao* waterVao;
    Vbo* water_render;
    vector<Face>waterFace;
    bool IsFaceGenerateComplete;
    bool IsLoadFace;
    bool IsFaceLoadToGpu;
    Section();
    void ResetState();
    void PossDataToGpu();
    ~Section();
};

#endif // SECTION_H
