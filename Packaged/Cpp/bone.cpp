#include "Include/bone.h"
Bone::Bone(GLuint id_,aiNodeAnim*channel){
    name=channel->mNodeName.C_Str();
    id=id_;
    ////////////////////////////////////关键位置
    Uint position_size=channel->mNumPositionKeys;
    key_position.resize(position_size);
    for(Uint i=0;i<position_size;++i)
    {
        KeyPosition&data= key_position[i];
        auto&p=channel->mPositionKeys[i];
        data.timestamp=p.mTime;
        data.position={p.mValue.x,p.mValue.y,p.mValue.z};
    }
    /////////////////////////////////////关键旋转
    Uint rotation_size=channel->mNumRotationKeys;
    key_rotation.resize(rotation_size);
    for(Uint i=0;i<rotation_size;++i)
    {
        KeyRotation&data= key_rotation[i];
        auto&p=channel->mRotationKeys[i];
        data.timestamp=p.mTime;
        data.rotation={p.mValue.w,p.mValue.x,p.mValue.y,p.mValue.z};
    }
    //////////////////////////////////////关键缩放
    Uint scale_size=channel->mNumScalingKeys;
    key_scale.resize(scale_size);
    for(Uint i=0;i<scale_size;++i)
    {
        KeyScale&data= key_scale[i];
        auto&p=channel->mScalingKeys[i];
        data.timestamp=p.mTime;
        data.scale={p.mValue.x,p.mValue.y,p.mValue.z};
    }
}

void Bone::update(float timestamp)
{
    Matrix translation = InterpolatePosition(timestamp);
    Matrix rotation = InterpolateRotation(timestamp);
    Matrix scale = InterpolateScale(timestamp);
    LocalTransform= translation * rotation * scale;
}

GLuint Bone::GetPositionIndex(float timestamp)
{
    return BinarySearch(key_position, timestamp);
}

GLuint Bone::GetRotationIndex(float timestamp)
{
    return BinarySearch(key_rotation, timestamp);
}

GLuint Bone::GetScaleIndex(float timestamp)
{
    return BinarySearch(key_scale, timestamp);
}

Matrix Bone::InterpolatePosition(float timestamp)
{
    Matrix res;
    if(key_position.size()==1)
    {
        res.translate(key_position[0].position);
        return res;
    }
    GLuint index0=GetPositionIndex(timestamp);
    auto&p0=key_position[index0-1];
    auto&p1=key_position[index0];
    float scaleFactor=GetScaleFactor(p0.timestamp,timestamp,p1.timestamp);
    vec3 mix=p0.position.mix(p1.position,scaleFactor);
    res.translate(mix);
    return res;
}

Matrix Bone::InterpolateRotation(float timestamp)
{
    if (key_rotation.size()==1)
    {
        auto rotation=key_rotation[0].rotation.normalize();
        return Matrix::ConvertQuaternionToMat4(rotation);
    }
    GLuint index=GetRotationIndex(timestamp);
    auto&p0=key_rotation[index-1];
    auto&p1=key_rotation[index];
    float scaleFactor = GetScaleFactor(p0.timestamp,timestamp,p1.timestamp);
    vec4 finalRotation =slerp(p0.rotation,p1.rotation, scaleFactor);
    finalRotation = finalRotation.normalize();
    return Matrix::ConvertQuaternionToMat4(finalRotation);
}

Matrix Bone::InterpolateScale(float timestamp)
{
    Matrix res;
    if(key_scale.size()==1)
    {
        res.scale(key_scale[0].scale);
        return res;
    }
    GLuint index0=GetScaleIndex(timestamp);
    auto&p0=key_scale[index0-1];
    auto&p1=key_scale[index0];
    float scaleFactor=GetScaleFactor(p0.timestamp,timestamp,p1.timestamp);
    vec3 mix=p0.scale.mix(p1.scale,scaleFactor);
    res.scale(mix);
    return res;
}

float Bone::GetScaleFactor(const float&begin, const float& current, const float&end)
{
    return (current-begin)/(end-begin);
}

vec4 Bone::slerp(const vec4 &x, const vec4 &y, float a)
{
    auto z = y;
    float cosTheta = x.dot(y);
    if(cosTheta < 0.0f)
    {
        z =vec4(0.0)-y;
        cosTheta = -cosTheta;
    }
     if(cosTheta >1.0-1.19209e-07)
    {
        return vec4(
            x.x*(1.0f-a)+z.x*a,
            x.y*(1.0f-a)+z.y*a,
            x.z*(1.0f-a)+z.z*a,
            x.w*(1.0f-a)+z.w*a);
    }
    else
    {
        float angle = acos(cosTheta);
        return (x*sin((1.0f - a) * angle)+z*sin(a * angle))/sin(angle);
    }
}

Bone::~Bone()
{

}
