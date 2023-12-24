#ifndef BUFFERBASE
#define BUFFERBASE
#include"Include.h"
template <GLuint BUFFERTYPE> class BufferBase {
protected:
  GLuint id;
public:
  BufferBase(GLuint size, void *data = 0);
  BufferBase(BufferBase&buffer);
   void bind() { api->glBindBuffer(BUFFERTYPE, id); }
   void unbind() { api->glBindBuffer(BUFFERTYPE, 0); }
   void setdata(GLuint size, GLuint offset, void *data);
  void setdata(GLuint size, void *data) { setdata(size, 0, data);}
  template<class T,class...ARG>
  void setdata_arglist(GLuint offset,const T&data,const ARG&...arg);
  void *map(GLuint size, GLuint offset = 0,
            GLuint mask = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
  void unmap();
  void readdata(void* buffer,GLuint size);
   GLuint reserve();
  GLuint getid() { return id; }
  ~BufferBase();
};
template <GLuint BUFFERTYPE>
template<class T, class...ARG>
void BufferBase<BUFFERTYPE>::setdata_arglist(GLuint offset,const T &data,const ARG&...arg)
{
  setdata(sizeof(T),offset,(void*)&data);
  if constexpr(sizeof...(arg)){
      setdata_arglist(offset+sizeof(T),arg...);
  }
  else return;
}
////
template <GLuint BUFFERTYPE>
BufferBase<BUFFERTYPE>::BufferBase(GLuint size, void *data) {
  api->glGenBuffers(1, &id);
  bind();
  api->glBufferData(BUFFERTYPE, size, data, GL_STATIC_DRAW);
}
////
template <GLuint BUFFERTYPE>
BufferBase<BUFFERTYPE>::BufferBase(BufferBase&buffer) {
  id =buffer.id;
  bind();
}
///
template <GLuint BUFFERTYPE>
void BufferBase<BUFFERTYPE>::setdata(GLuint size, GLuint offset, void *data) {
 api->glBufferSubData(BUFFERTYPE, offset, size, data);
}
///
template <GLuint BUFFERTYPE>
void *BufferBase<BUFFERTYPE>::map(GLuint size, GLuint offset, GLuint mask) {
  void *ptr =api->glMapBufferRange(BUFFERTYPE, offset, size, mask);
  return ptr;
}
///
template <GLuint BUFFERTYPE> void BufferBase<BUFFERTYPE>::unmap() {
  api->glUnmapBuffer(BUFFERTYPE);
}

template<GLuint BUFFERTYPE>
void BufferBase<BUFFERTYPE>::readdata(void* buffer, GLuint size)
{
    api->glGetBufferSubData(BUFFERTYPE, 0, size, buffer);
}

template<GLuint BUFFERTYPE>
GLuint BufferBase<BUFFERTYPE>::reserve()
{
  id=0;
  return id;
}
///
template <GLuint BUFFERTYPE> BufferBase<BUFFERTYPE>::~BufferBase() {
  if (id)
    api->glDeleteBuffers(1, &id);
}
////////
#endif
