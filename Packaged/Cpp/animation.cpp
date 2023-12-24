#include "Include/animation.h"

void Animation::ReadMissingBones(aiAnimation*animation_,Model&model)
{
    auto&bone_map=model.getBoneMap();
    auto& boneCounts = model.getBoneNums();;
    for(Uint i=0;i<animation_->mNumChannels;++i)
    {
        auto*channel=animation_->mChannels[i];
        string name=channel->mNodeName.C_Str();
        if(bone_map.find(name)==bone_map.end())
        {
            bone_map[name].id = boneCounts++;
        }
        Bones.push_back(Bone(bone_map[name].id,channel));
    }
    BonesInfo = bone_map;
}

void Animation::ReadHeirarchyData(AnimationNodeData &dest, const aiNode *src)
{
    dest.name=src->mName.C_Str();
    dest.children.resize(src->mNumChildren);
    dest.transformation=Matrix::ConvertToColumnFormat(&(src->mTransformation.a1));
    for(Uint i=0;i<src->mNumChildren;++i)
    {
        AnimationNodeData&temp=dest.children[i];
        ReadHeirarchyData(temp,src->mChildren[i]);
    }
}

Bone* Animation::FindBone(const string& name)
{
    auto iter = std::find_if(Bones.begin(),Bones.end(),
        [&](const Bone& Bone)
        {
            return Bone.name== name;
        }
    );
    if (iter == Bones.end()) return nullptr;
    else return &(*iter);
}

Animation::Animation(const char *file,Model*model)
{
    Importer impoter;
    auto*scene=impoter.ReadFile(file, aiProcess_Triangulate);
    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode)
    {
       std::cout<<impoter.GetErrorString()<<std::endl;
        return;
    }

    //////////////////////////////////加载动画
        auto*animation_=scene->mAnimations[0];
        name=animation_->mName.C_Str();
        duration=animation_->mDuration;
        TicksPerSecond=animation_->mTicksPerSecond;
        ReadHeirarchyData(RootNode, scene->mRootNode);
        ReadMissingBones(animation_,*model);
}

Animation::~Animation()
{
 
}
