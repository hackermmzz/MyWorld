#include "octree.h"

OctreeNode::OctreeNode()
	:box({},{})
{
	for (auto& ele : node)ele = 0;
	data = 0;
}

OctreeNode::OctreeNode(const AABB& box_)
	:box(box_)
{

}

OctreeNode* Octree::BuildOctree(const AABB& aabb, Uint level)
{
	auto* node = new OctreeNode(aabb);
	if (level == 0)
		for (auto& ele : node->node)ele = 0;
	else
	{
		vec3 center = (node->box.GetMinVec()+node->box.GetMaxVec())/ 2;
		vec3 halfSize= (node->box.GetMaxVec()-node->box.GetMinVec())/2;
		//构建8个包围盒
	//	AABB childbox
	}
	return node;
}

Octree::Octree(const AABB& root_, Uint level)
{
	root = new OctreeNode(root_);

}
