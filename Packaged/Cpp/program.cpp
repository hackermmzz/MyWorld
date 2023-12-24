#include "Include/program.h"

Program::Program(const char *vertex_code, const char *geometry_code, const char *fragment_code, GLboolean reserved)
{
    Shader vertex = Shader(vertex_code, GL_VERTEX_SHADER,reserved);
    Shader fragment = Shader(fragment_code, GL_FRAGMENT_SHADER,reserved);
    Shader geometry=Shader(geometry_code,GL_GEOMETRY_SHADER,reserved);
    id= api->glCreateProgram();
    if (!(vertex.getid() && fragment.getid()&&geometry.getid()))
        return;
    api->glAttachShader(id, vertex.getid());
    api->glAttachShader(id, fragment.getid());
    api->glAttachShader(id,geometry.getid());
    api->glLinkProgram(id);
    geterror(id);
    ///
    bind();
}

Program::Program(const char *vertex_code, const char *fragment_code, GLboolean reserved)
{
    Shader vertex = Shader(vertex_code, GL_VERTEX_SHADER,reserved);
    Shader fragment = Shader(fragment_code, GL_FRAGMENT_SHADER,reserved);
    id= api->glCreateProgram();
    if (!(vertex.getid() && fragment.getid()))
        return;
    api->glAttachShader(id, vertex.getid());
    api->glAttachShader(id, fragment.getid());
    api->glLinkProgram(id);
    geterror(id);
    ///
    bind();
}
Program::Program(const char *vertexfile, const char *fragfile)
{
    Shader vertex = Shader(vertexfile, GL_VERTEX_SHADER);
    Shader fragment = Shader(fragfile, GL_FRAGMENT_SHADER);
    id= api->glCreateProgram();
    if (!(vertex.getid() && fragment.getid()))
        return;
    api->glAttachShader(id, vertex.getid());
    api->glAttachShader(id, fragment.getid());
    api->glLinkProgram(id);
    geterror(id);
    ///
    bind();
}
Program::Program(const char *vertexfile, const char *geometryfile, const char *fragfile)
{
    Shader vertex = Shader(vertexfile, GL_VERTEX_SHADER);
    Shader fragment = Shader(fragfile, GL_FRAGMENT_SHADER);
    Shader geometry=Shader(geometryfile,GL_GEOMETRY_SHADER);
    id= api->glCreateProgram();
    if (!(vertex.getid() && fragment.getid()&&geometry.getid()))
     return;
    api->glAttachShader(id, vertex.getid());
    api->glAttachShader(id, fragment.getid());
    api->glAttachShader(id,geometry.getid());
    api->glLinkProgram(id);
    geterror(id);
    ///
    bind();
}

Program::Program(const char* vertexfile, const char* gemoetryfile,const vector<std::string>& varyings)
{
    Shader vertexShader(vertexfile, GL_VERTEX_SHADER);
    Shader* gemoetryShader = 0;
    if (gemoetryfile)gemoetryShader = new Shader(gemoetryfile, GL_GEOMETRY_SHADER);
    id = api->glCreateProgram();
    if (!(vertexShader.getid()&&(!gemoetryShader||gemoetryShader->getid())))return;
    api->glAttachShader(id, vertexShader.getid());
    if(gemoetryShader)
    api->glAttachShader(id, gemoetryShader->getid());
    const char* VaryingName[1024] = {};
    for (int i = 0; i < varyings.size(); ++i)
    {
        VaryingName[i] = varyings[i].c_str();
    }
    api->glTransformFeedbackVaryings(id, varyings.size(),VaryingName, GL_INTERLEAVED_ATTRIBS);
    api->glLinkProgram(id);
    ////////////////////////////////////
    geterror(id);
    bind();
    ////////////////////////////////////
    if (gemoetryShader)delete gemoetryShader;
}

Program::Program(const char *programfile)
{
    id = 0;
      FILE *file = fopen(programfile, "r");
      if (file == 0)
        return;
      id = api->glCreateProgram();
      char buffer[PROGRAM_BINARY_MAX_LENGTH];
      GLenum format;
      int length;
      fread(&format, sizeof(format), 1, file);
      fread(&length, sizeof(length), 1, file);
      fread(buffer, 1, PROGRAM_BINARY_MAX_LENGTH, file);
      api->glProgramBinary(id, format, buffer, length);
      int status = 0;
      api->glGetProgramiv(id, GL_LINK_STATUS, &status);
      if (status == GL_FALSE)
        printf("Fail to load %s!\n", programfile);
      fclose(file);
      bind();
}

Program::Program(GLuint id_)
{
 id=id_;
}
void Program::bind() {api->glUseProgram(id); }
void Program::unbind() { api->glUseProgram(0); }

GLuint Program::getid()
{
    return id;
}
void Program::setvec4(const char *name, GLfloat *val) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
 api->glUniform4fv(location, 1, val);
}
/////////////
void Program::setvec4(const char *name, GLfloat val1, GLfloat val2,
                      GLfloat val3, GLfloat val4) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform4f(location, val1, val2, val3, val4);
}

void Program::setvec4(const char *name, vec4 &val)
{
  setvec4(name,val.value_ptr());
}

void Program::setvec4(const char *name, vector<vec4> &val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setvec4(temp.c_str(),val[i]);
  }
}
///////////
void Program::setmat4(const char *name, Matrix &mat) {

  int location =getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniformMatrix4fv(location, 1, 0, mat.value_ptr());
}

///////////
void Program::setfloat(const char *name, GLfloat val) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform1f(location, val);
}
/////////
void Program::setvec2(const char *name, GLfloat val1, GLfloat val2) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform2f(location, val1, val2);
}

void Program::setvec2(const char *name,vec2&val)
{
  setvec2(name,val.value_ptr());
}

void Program::setvec2(const char *name,vector<vec2>&val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setvec2(temp.c_str(),val[i]);
  }
}
////////
void Program::setvec2(const char *name, GLfloat *val) {
      int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform2fv(location, 1, val);
    }
////////
void Program::setvec3(const char *name, GLfloat *val) {

  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform3fv(location, 1, val);
}

void Program::setvec3(const char *name, vec3 &val)
{
  setvec3(name,val.value_ptr());
}

void Program::setvec3(const char *name, vector<vec3> &val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setvec3(temp.c_str(),val[i]);
  }
}
/////
void Program::setivec3(const char *name, GLint *val) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform3iv(location, 1, val);
}

void Program::setivec3(const char *name, ivec3 &val)
{
  setivec3(name,val.value_ptr());
}

void Program::setivec3(const char *name, vector<ivec3> &val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setivec3(temp.c_str(),val[i]);
  }
}
///////
void Program::setvec3(const char *name, GLfloat val1, GLfloat val2,
                      GLfloat val3) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
 api->glUniform3f(location, val1, val2, val3);
}
//////
void Program::setmat3(const char *name, GLfloat *val) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniformMatrix3fv(location, 1, 0, val);
}
//////////
void Program::setint(const char *name, GLint val) {
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform1i(location, val);
}

void Program::setint(const char *name, vector<int> &val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setint(temp.c_str(),val[i]);
  }
}

void Program::setuint(const char *name, GLuint val)
{
  int location = getUniformlocation(name, *this);
  if (location < 0)
    return;
  api->glUniform1ui(location, val);
}

void Program::setuint(const char *name, vector<Uint> &val)
{
  std::string name_=name+std::string("[");
  Uint size=val.size();
  for(Uint i=0;i<size;++i)
  {
    std::string temp=name_+std::to_string(i)+"]";
    setuint(temp.c_str(),val[i]);
  }
}
///////////
void Program::setuniformblock(const char *name, GLuint index) {
  int location =api->glGetUniformBlockIndex(id, name);
  if (location < 0)
    return;
  api->glUniformBlockBinding(id, location, index);
}

void Program::setShaderStorageBlock(const char *name, GLuint index)
{
  GLuint location = api->glGetProgramResourceIndex(id,GL_SHADER_STORAGE_BLOCK, name);
  if (location < 0)
    return;
  api->glShaderStorageBlockBinding(id,location,index);
}
/////////
////////////
Program::~Program() {
  if (id)
   api->glDeleteProgram(id);
}
bool Program::compileprogram(const char *vertexfile, const char *fragfile, const char *tar)
{
    FILE *file = fopen(vertexfile, "r");
     FILE *file2 = fopen(fragfile, "r");
     if (file == 0 || file2 == 0)
       return 0;
     Program program(vertexfile, fragfile);
     GLint support = 0;
     api->glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, &support);
     if (support < 0)
       return 0;
     char buffer[PROGRAM_BINARY_MAX_LENGTH];
     GLenum format;
     int length;
     api->glGetProgramBinary(program.getid(), PROGRAM_BINARY_MAX_LENGTH, &length,
                        &format,buffer);
     FILE *file3 = fopen(tar, "w");
     fwrite(&format, sizeof(format), 1, file3);
     fwrite(&length, sizeof(length), 1, file3);
     fwrite(buffer, 1, length, file3);
     fclose(file3);
     fclose(file);
     fclose(file2);
     return 1;
}
bool Program::geterror(GLuint program) {
  int status = 0;
  api->glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
   QString SaveToFilePath=QDir::currentPath()+QString("\\ShaderCompileError.txt");
    QFile f(SaveToFilePath);
   f.open(QIODevice::Append);
    char *info=new char[SHADER_ERROR_MAX_LENGTH+1];
    api->glGetProgramInfoLog(program, SHADER_ERROR_MAX_LENGTH, 0, info);
    strcat(info, "Program");
    strcat(info, "\n--------------------------------------\n");
    char*date=QDateTime::currentDateTime().toString("hh:mm:ss").toUtf8().data();
    f.write(date,strlen(date));
    f.write("\n",1);
    f.write(info,strlen(info));
    f.close();
    delete []info;
    return 0;
  }
  return 1;
}
int Program::getUniformlocation(const char *name, Program &program) {
  int location = api->glGetUniformLocation(program.id, name);
  return location;
}
