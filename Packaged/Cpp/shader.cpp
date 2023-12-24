#include "Include/shader.h"
void Shader::GetShaderError(const char*file,GLuint id) {
    int success;
    api->glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success)
        return;
    QString SaveToFilePath=QDir::currentPath()+QString("/ShaderCompileError.txt");
     QFile f(SaveToFilePath);
     f.open(QIODevice::Append);
     char*info=new char[SHADER_ERROR_MAX_LENGTH+1];
    api->glGetShaderInfoLog(id, SHADER_ERROR_MAX_LENGTH, 0, info);
    strcat(info,file);
    strcat(info, "\n--------------------------------------\n");
    char*date=QDateTime::currentDateTime().toString("hh:mm:ss").toUtf8().data();
    f.write(date,strlen(date));
    f.write("\n",1);
   f.write(info,strlen(info));
    delete[]info;
}

Shader::Shader(const char *file, GLenum TYPE)
{
    static char data[SHADER_SIZE+1];
    id=api->glCreateShader(TYPE);
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QDataStream data_stream(&f);
    data_stream.readRawData(data,f.size());
    char*data_=&data[0];
    data_[f.size()]=0;
    api->glShaderSource(id,1,&data_,0);
    api->glCompileShader(id);
    GetShaderError(file,id);
}

Shader::Shader(const char *code, GLenum TYPE, GLboolean reserved)
{
    id=api->glCreateShader(TYPE);
    api->glShaderSource(id,1,&code,0);
    api->glCompileShader(id);
    GetShaderError("CodeFile",id);
}

GLuint Shader::getid()
{
    return id;
}

Shader::~Shader()
{
    if(id)
    api->glDeleteShader(id);
}
