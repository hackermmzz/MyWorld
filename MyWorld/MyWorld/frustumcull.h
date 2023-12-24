#ifndef FRUSTUMCULL_H
#define FRUSTUMCULL_H
#include"globalsource.h"
#include"chunk.h"
#include"world.h"
/// ///////////////////////////////采用非对称八叉树裁剪
struct WorldNode {
	ivec3 point[8];
	WorldNode* child[8];
};
extern WorldNode* WorldRoot;
////////////////////////////////
WorldNode* BuildWorldNode(int x_start, int x_end, int y_start, int y_end, int z_start, int z_end);
void Canculate(WorldNode* node, vector<Section*>&store);
////////////////////////////////视锥裁剪出处于视锥里面的section
vector<Section*>& FrustumCull();
int JudgeBoxIsInSamePlane(const vec3*point,Face&face);//判断aabb盒子八个顶点是否位于一个平面的同一侧
//-1 在外面  0 相交 1 在里面
#endif // FRUSTUMCULL_H
