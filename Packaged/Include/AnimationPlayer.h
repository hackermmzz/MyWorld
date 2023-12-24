#ifndef ANIMATIONPLAYER
#define ANIMATIONPLAYER
#include"animation.h"
///////////////////////////////////////////////
class AnimationPlayer
{
private:
	std::vector<Matrix> m_FinalBoneMatrices;
	Animation* m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;
public:
	AnimationPlayer(Animation* animation);
	void UpdateAnimation(float dt);
	void PlayAnimation(Animation* pAnimation);
	void CalculateBoneTransform(AnimationNodeData* node, Matrix parentTransform);
	vector<Matrix> GetFinalBoneMatrices();
	~AnimationPlayer();
};
/////////////////////////////////////////////
#endif