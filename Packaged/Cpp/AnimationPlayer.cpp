#include "AnimationPlayer.h"

 AnimationPlayer::AnimationPlayer(Animation* animation)
{
	m_CurrentTime = 0.0;
	m_CurrentAnimation = animation;

	m_FinalBoneMatrices.reserve(100);

	for (int i = 0; i < 100; i++)
		m_FinalBoneMatrices.push_back(Matrix());
}

void AnimationPlayer::UpdateAnimation(float dt)
 {
	 m_DeltaTime = dt;
	 if (m_CurrentAnimation)
	 {
		 m_CurrentTime += m_CurrentAnimation->TicksPerSecond * dt;
		 m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->duration);
		 CalculateBoneTransform(&m_CurrentAnimation->RootNode, Matrix());
	 }
 }

void AnimationPlayer::PlayAnimation(Animation* pAnimation)
{
	m_CurrentAnimation = pAnimation;
	m_CurrentTime = 0.0f;
}

void AnimationPlayer::CalculateBoneTransform(AnimationNodeData* node, Matrix parentTransform)
{
	std::string& nodeName = node->name;
	Matrix nodeTransform = node->transformation;
	Bone* Bone = m_CurrentAnimation->FindBone(nodeName);
	if (Bone)
	{
		Bone->update(m_CurrentTime);
		nodeTransform = Bone->LocalTransform;
	}
	Matrix globalTransformation = parentTransform * nodeTransform;
	auto boneInfoMap = m_CurrentAnimation->BonesInfo;
	if (boneInfoMap.find(nodeName) != boneInfoMap.end())
	{
		auto& info = boneInfoMap[nodeName];
		int index =info.id;
		Matrix offset =info.BoneSpace;
		m_FinalBoneMatrices[index] = globalTransformation * offset;
	}
	int size = node->children.size();
	for (int i = 0; i < size; i++)
		CalculateBoneTransform(&node->children[i], globalTransformation);
}

vector<Matrix> AnimationPlayer::GetFinalBoneMatrices()
{
	return m_FinalBoneMatrices;
}


AnimationPlayer::~AnimationPlayer()
{
}