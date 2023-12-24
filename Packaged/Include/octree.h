#ifndef OCTREE_H
#define OCTREE_H
#include"AABB.h"
/////////////////////////////////
struct OctreeNode{
	AABB box;
	OctreeNode* node[8];
	void* data;
	OctreeNode();
	OctreeNode(const AABB& box);
};
/////////////////////////////////
class Octree
{
private:
	OctreeNode* root;
	OctreeNode* BuildOctree(const AABB& aabb,Uint level);
public:
	Octree(const AABB& root, Uint level);

};
/////////////////////////////////
#endif // OCTREE_H
