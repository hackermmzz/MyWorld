#ifndef TRANSFORMFEEDBACK_H
#define TRANSFORMFEEDBACK_H
#include"Include.h"
#include"BufferBase.hpp"
////////////////////////////////////
class TransformFeedBack {
private:
	GLuint id;
public:
	TransformFeedBack();
	void bind();
	void BindTransformBuffer(GLuint id,GLuint binding=0);
	void Begin(GLenum mode=GL_POINTS);
	void End();
	GLuint getid();
	~TransformFeedBack();
};
////////////////////////////////////
#endif // !TRANSFORMFEEDBACK_H
