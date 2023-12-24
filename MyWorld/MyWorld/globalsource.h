#ifndef GLOBALSOURCE_H
#define GLOBALSOURCE_H
#include<Include/Headers.h>
#include"queue"
#include"others.h"
#include"PerlinNoise.hpp"
#include"BlockType.h"
#include<set>
using namespace std;
using siv::PerlinNoise;
////////////////////////////////////
extern GLuint window_width;//窗口宽
extern GLuint window_height;//窗口高
////////////////////////////////////
extern int mouse_movement_offset_x;//鼠标在x轴的偏移
extern int mouse_movement_offset_y;//鼠标在y轴的偏移
//////////////////////////////////////
extern Camera camera;//人物摄像机
extern Matrix camera_view;//视锥矩阵
extern Matrix camera_view_inverse;//视图矩阵逆矩阵
extern size_t camera_mode;//摄像机的模式,0为第一人称,1为第三人称,2为第二人称
extern float real_camera_distance;//摄像机为第三人称时距离人物距离
extern ivec2 camera_chunk;//人物在所在chunk的坐标
extern ivec3 camera_section;//人物所在section的坐标
extern GLenum BiomeTypeAround[3][3];//人物周围的生物群落类型
extern Ubo*camera_ubo;//按顺序包含projection*view porjection view
extern Matrix camera_projection;//摄像机裁剪矩阵
extern Face camera_face[6];//视锥体6个面
#define CAMERA_UBO_BINDING 0//摄像机裁剪矩阵的绑定点
#define CAMERA_PROJECTION_FOV 40.0f//摄像机俯角
#define CAMERA_PROJECTION_NEAR 0.1//近平面
#define CAMERA_PROJECTION_FAR 1000//远平面
////////////////////////////////////
extern  long long render_begin;//每一帧开始的时间
extern  long long render_end;//每一帧结束的时间
extern  long long render_time;
extern float fps;//帧率
////////////////////////////////////事件
extern queue<size_t>EventQueue;//事件队列
////////////////////////////////////
extern QOpenGLWidget*OpenglWidget;//openglwidget
extern Uint Face_Render_Nums;//渲染的面的数量
extern Uint Section_Render_Nums;//渲染的section数量
////////////////////////////////////
extern int WORLD_DEFAULT_SEED;
#define SECTION_SIZE 16//一个区块大小
#define CHUNK_SIZE 16//一个chunk包含的区块数量
#define TERRAIN_NOISE_FBM 6//分形噪声采样次数
#define CHUNK_RENDER_SIZE 31//地图中会被渲染的chunk的区域
#define CHUNK_LOAD_SIZE (CHUNK_RENDER_SIZE+2)//地图加载的所有chunk的区域
///////////////////////////////////////
extern ThreadPool*threadPool;
#define THREAD_POOL_NUMS 20//线程池个数
//////////////////////////////////////////
extern Program*BlockRenderProgram;//渲染方块着色器
///////////////////////////////////////////
extern Texture2DGeneral* skybox;//天空盒纹理
/////////////////////////////////////////////
extern PerlinNoise ContinentalNoise;//大陆性噪声产生器
extern PerlinNoise ErosionNoise;//腐蚀性噪声产生器
extern PerlinNoise PeaksNoise;//高峰性噪声产生器
extern PerlinNoise HumidityNoise;//湿度噪声产生器
extern PerlinNoise TemperatureNoise;//温度噪声产生器
#define CONTINENALNOISE_WEIGHT 0.6
#define EROSIONNOISE_WEIGHT 0.2
#define PEAKNOISE_WEIGHT 0.2
#define BED_ROCK_DEPTH 5
#define CONTINENTALNOISEFREQ (SECTION_SIZE*CHUNK_LOAD_SIZE)
#define EROSIONNOISEFREQ (SECTION_SIZE*2)
#define PEAKNOISEFREQ (SECTION_SIZE*8)
#define HUMIDITYNOISEFREQ (SECTION_SIZE*8)
#define TEMPERATURENOISEFREQ (SECTION_SIZE*8)
///////////////////////////////////////////雾化参数
#define FROG_MAX_DISTANCE 350
#define FROG_MIN_DISTANCE 300
///////////////////////////////////////////云朵纹理
extern Texture2DGeneral*cloud;
extern Program*CloudRenderProgram;
/////////////////////////////////////////
#define BLOCK_TARGET_MAX_DISTANCE 5
/////////////////////////////////////////
extern bool Show_Info;//显示一些信息
////////////////////////////////////////
extern map<ivec3,Block>BlockChanged;//被人物改变的区块
extern map<ivec3, Block>LightBlock;//会发光的方块
////////////////////////////////////////
enum BiomeType{PLAIN,GRASSLAND,RAINFOREST,FOREST,SNOWFIELD,DESERT,OCEAN};
////////////////////////////////////////
extern Program* WaterRenderProgram;//渲染水
#define WATER_ALTITUDE (SECTION_SIZE*CHUNK_SIZE/4) //当区块存在低于该位置时才可能生成河流
#define OCEAN_WEIGHT 0.5//海洋占比
///////////////////////////////////////
#define BIOMEMAP_SIZE (CHUNK_LOAD_SIZE*5)
///////////////////////////////////////
#define TNT_BOOM_RANGE 3//TNT爆炸半径
////////////////////////////////////////
extern DeferredRendering* GBuffer;//延时渲染gbuffer
extern Program* GBufferProgram;
////////////////////////////////////////
#define LIGHT_SSBO_BUFFER_BINDING 1//光源ssbo的绑定点
#define FIREFLY_SSBO_BUFFER_BINDING 2//萤火虫附着物绑定点
////////////////////////////////////////
#define GAME_MAX_FPS 120//游戏最大帧率
#endif // GLOBALSOURCE_H
