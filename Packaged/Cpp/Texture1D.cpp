#include "Texture1D.h"

Texture1D::Texture1D(GLuint size, GLenum internalformat, GLenum format, GLenum type, void* data)
{
	api->glGenTextures(1, &id);
	api->glBindTexture(GL_TEXTURE_1D, id);
	api->glTexImage1D(GL_TEXTURE_1D, 0, internalformat, id, 0, format,type,data);
	bind();
	////////////////////////////
	wrap(GL_REPEAT);
	filter(GL_NEAREST);
}

void Texture1D::bind(GLuint binding)
{
	api->glActiveTexture(GL_TEXTURE0 + binding);
	api->glBindTexture(GL_TEXTURE_1D, id);
}

void Texture1D::wrap(GLenum type)
{
api->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, type);
}

void Texture1D::filter(GLenum type)
{
api->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,type);
api->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, type);
}

Texture1D::~Texture1D()
{
	if (id)api->glDeleteTextures(1, &id);
}
