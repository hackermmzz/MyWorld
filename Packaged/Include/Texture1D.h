#ifndef TEXTURE1D_H
#define TEXTURE1D_H
#include"Include.h"
///////////////////////////////////
class Texture1D {
private:
	GLuint id;
public:
	Texture1D(GLuint size, GLenum internalformat, GLenum format, GLenum type, void* data=0);
	void bind(GLuint binding = 0);
	void wrap(GLenum type);
	void filter(GLenum type);
	~Texture1D();
};
///////////////////////////////////
#endif // !TEXTURE1D_H
