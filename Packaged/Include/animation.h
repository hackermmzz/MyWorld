#ifndef ANIMATION_H
#define ANIMATION_H
#include"Include.h"
#include"model.h"
#include"bone.h"
#include"ubo.h"
//////////////////////////////////////////
struct AnimationNodeData
{
    Matrix transformation;
    string name;
    vector<AnimationNodeData> children;
};
struct  Animation
{
    ////////////////////////////////////////////
    string name;
    float duration;
    int TicksPerSecond;
    vector<Bone>Bones;
    AnimationNodeData RootNode;
    unordered_map<string, BoneInfo>BonesInfo;
    float CurrentTime;
    void ReadMissingBones(aiAnimation*animation,Model&model);
    void ReadHeirarchyData(AnimationNodeData&dest, const aiNode* src);
    Bone* FindBone(const string&name);
    Animation(const char*animation_file,Model*model);
    ~Animation();
};
#endif // ANIMATION_H
