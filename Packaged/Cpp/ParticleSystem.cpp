#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vao* vao_[2], Vbo* buffer_[2], GLuint LaunchersNum_)
{
	LaunchersNum = LaunchersNum_;
	Reset();
	////////////////////////////
	for (int i = 0; i < 2; ++i)
	{
		vao[i] = vao_[i];
		buffer[i] = buffer_[i];
		tfb[i] = new TransformFeedBack;
		tfb[i]->BindTransformBuffer(buffer_[(i+1)&1]->getid(), 0);
	}
}

void ParticleSystem::Reset()
{
	init=0;
	index=0;
}

void ParticleSystem::Update(GLenum mode)
{
	auto& tfb_ =*tfb[index];
	tfb_.bind();
	tfb_.Begin();
	vao[index]->bind();
	if (!init)
	{
		init = 1;
		api->glDrawArrays(mode, 0, LaunchersNum);
	}
	else
		Draw(mode);
	index = (index + 1) & 1;
	tfb_.End();
}

Vbo* ParticleSystem::GetCurrentRenderBuffer()
{
	return buffer[index];
}

void ParticleSystem::Draw(GLenum mode)
{
	api->glDrawTransformFeedback(mode, tfb[(index+1)&1]->getid());
}

ParticleSystem::~ParticleSystem()
{
	for (auto& tfb_ : tfb)
		if (tfb_)delete tfb_;
}
