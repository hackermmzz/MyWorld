#include "TransformFeedBack.h"

TransformFeedBack::TransformFeedBack()
{
	api->glGenTransformFeedbacks(1, &id);
	bind();
}

void TransformFeedBack::bind()
{
	api->glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, id);
}

void TransformFeedBack::BindTransformBuffer(GLuint id, GLuint binding)
{
	api->glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, binding,id);
}

void TransformFeedBack::Begin(GLenum mode)
{
	api->glEnable(GL_RASTERIZER_DISCARD);
	api->glBeginTransformFeedback(mode);
}

void TransformFeedBack::End()
{
	api->glEndTransformFeedback();
	api->glDisable(GL_RASTERIZER_DISCARD);
}

GLuint TransformFeedBack::getid()
{
	return id;
}

TransformFeedBack::~TransformFeedBack()
{
	if (id)api->glDeleteTransformFeedbacks(1, &id);
}
