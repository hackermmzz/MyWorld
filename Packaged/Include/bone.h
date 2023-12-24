#ifndef BONE_H
#define BONE_H
#include"model.h"
struct Bone
{
    struct KeyPosition{
        vec3 position;
        float timestamp;
    };
    struct KeyRotation{
        vec4 rotation;//这里拿vec4向量代表四元数
        float timestamp;
    };
    struct KeyScale{
        vec3 scale;
        float timestamp;
    };
    vector<KeyPosition>key_position;
    vector<KeyRotation>key_rotation;
    vector<KeyScale>key_scale;
    string name;
    GLuint id;
    Matrix LocalTransform;
    Bone(GLuint id,aiNodeAnim*channel);
    void update(float timestamp);
    /////////////////////////////////
    template<class T>
    GLuint BinarySearch(vector<T>&source,float timestamp);
    ////////////////////////////////////
    GLuint GetPositionIndex(float timestamp);
    GLuint GetRotationIndex(float timestamp);
    GLuint GetScaleIndex(float timestamp);
    Matrix InterpolatePosition(float timestamp);
    Matrix InterpolateRotation(float timestamp);
    Matrix InterpolateScale(float timestamp);
    float GetScaleFactor(const float&begin, const float& current, const float&end);
    vec4 slerp(const vec4&x,const vec4&y,float a);
    ~Bone();
};

#endif // BONE_H

template<class T>
GLuint Bone::BinarySearch(vector<T>& source, float timestamp)
{
    auto size = source.size();
    Uint left = 0, right = size - 1, mid;
    while (left < right)
    {
        mid = left +((right - left) >> 1);
        if (source[mid].timestamp <= timestamp)
            left = mid + 1;
        else right = mid;
    }
    return right;
}
