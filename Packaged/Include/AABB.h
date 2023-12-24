#ifndef AABB_H
#define AABB_H
#include"vec.hpp"
#include"raymatch.h"
//////////////////////////////////
class AABB {
private:
	vec3 minVec, maxVec;
public:
	AABB(const vec3& center, const vec3& size, bool reserved);
	AABB(const vec3& minVec,const vec3& maxVec);
	bool IsCollide(const AABB&box);
	bool IsIntersect(const Ray&ray);
	bool IsContainAABB(const AABB& box);
	vec3& GetMinVec();
	vec3& GetMaxVec();
};
/////////////////////////////////
#endif // !AABB_H
