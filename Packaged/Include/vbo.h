#ifndef VBO_H
#define VBO_H

#include "BufferBase.hpp"

class Vbo:public  BufferBase<GL_ARRAY_BUFFER>
{
public:
    Vbo(GLuint size, void *data = 0);
   void setpoint(GLuint location, GLenum value_type, GLuint num, GLuint step_size, GLuint offset = 0);
  void setpointiv(GLuint location, GLenum value_type, GLuint num, GLuint step_size, GLuint offset = 0);
  void setpoint(GLuint location, GLuint divisor);
   void disablepoint(GLuint location);
   ~Vbo();
};

#endif // VBO_H
