#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include"Include.h"
#include"TransformFeedBack.h"
#include"texture2dgeneral.h"
#include"vbo.h"
#include"vao.h"
#include"program.h"
using std::vector;
using std::string;
/////////////////////////////////////
class ParticleSystem
{
private:
	TransformFeedBack* tfb[2];
	Vao* vao[2];
	Vbo* buffer[2];
	int index;
	bool init;
	GLuint LaunchersNum;
public:
	ParticleSystem(Vao*vao[2],Vbo* buffer[2],GLuint LaunchersNum);
	void Reset();
	void Update(GLenum mode=GL_POINTS);
	Vbo* GetCurrentRenderBuffer();
	void Draw(GLenum mode=GL_POINTS);
	~ParticleSystem();
};
////////////////////////////////////////
#endif // PARTICLESYSTEM_H
