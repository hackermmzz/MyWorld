#ifndef INCLUDE_H
#define INCLUDE_H
/////
#include<qopenglwidget.h>
#include<qopenglfunctions_4_5_core.h>
#include"QDebug"
//////////////
#define OPENGLAPI QOpenGLFunctions_4_5_Core
extern OPENGLAPI*api;
void SetOpenGLApi(OPENGLAPI* api_);
/////////////buffer大小
#define SHADER_ERROR_MAX_LENGTH 1024*1024//1MB
#define PROGRAM_BINARY_MAX_LENGTH 4*1024*1024//4MB
#define SHADER_SIZE 1024*1024//1mb
//////////////mesh中采样器命名规则
#define TEXTURE_AMBIENT "ambient"
#define TEXTURE_DIFFUSE  "diffuse"
#define TEXTURE_SPECULAR "specular"
#define TEXTURE_NORMAL  "normal"
#define TEXTURE_HEIGHT "height"
/////////////光源成员名
#define LIGHT_POSITION "position"
#define LIGHT_DIRECTION "direction"
#define LIGHT_CONSTANT "constant"
#define LIGHT_LINEAR  "linear"
#define LIGHT_QUADRATIC  "quadratic"
#define LIGHT_CUTOFF    "cutoff"
#define LIGHT_OUTERCUTOFF  "outercutoff"
#define LIGHT_AMBIENT    "ambient"
#define LIGHT_DIFFUSE   "diffuse"
#define LIGHT_SPECULAR  "specular"
/////////////////////////////////定义读取天空和时文件的命名规范
#define CUBE_POSITIVE_X_NAME "right"
#define CUBE_POSITIVE_Y_NAME "top"
#define CUBE_POSITIVE_Z_NAME "front"
#define CUBE_NAGATIVE_X_NAME "left"
#define CUBE_NAGATIVE_Y_NAME "bottom"
#define CUBE_NAGATIVE_Z_NAME "back"
/////////////////////////////////
#define HDR_COLORBUFFER_TYPE GL_RGB16F//定义了HDR类型颜色缓冲的类型
#define SHADOW_DEPTHBUFFER_TYPE GL_DEPTH_COMPONENT32F//定义了阴影缓冲的内部类型
#define PI 3.1415926
#define LIGHT_ATTENUATION_CONSTANT 1.0
#define DIRECTIONALLIGHTSHADOW_MAX_LEVEL 10//定义了平行光CSM最大级
/////////////////////////////////
#define DEFERREDRENDRING_BUFFER_NAME  "gbuffer"//定义了延时渲染的buffer的命名规则
/////////////////////////////////
#define MODEL_MAX_BONES_INFLUENCE 4//规定了模型的受影响的最大骨头数量
#define MODEL_DEFAULT_PROCESS_MASK aiProcess_Triangulate|aiProcess_GenNormals|aiProcess_CalcTangentSpace//定义了默认处理模型的开关
/////////////////////////////////
#endif // INCLUDE_H
