#include "AABB.h"

AABB::AABB(const vec3& center, const vec3& size,bool reserved)
{
	vec3 half_size = size / 2;
	minVec = center - half_size;
	maxVec = center + half_size;
}

AABB::AABB(const vec3& minVec_, const vec3& maxVec_)
	:minVec(minVec_),maxVec(maxVec_)
{
}

bool AABB::IsCollide(const AABB& box)
{
	const vec3& minVec_ = box.minVec, maxVec_ = box.maxVec;
	if (minVec_.x >maxVec.x || maxVec_.x < minVec.x)return 0;
	if (minVec_.y > maxVec.y || maxVec_.y < minVec.y)return 0;
	if (minVec_.z > maxVec.z || maxVec_.z < minVec.z)return 0;
	return 1;

}

bool AABB::IsIntersect(const Ray& ray)
{
	auto& origin = ray.origin;
	auto& rayDir = ray.direction;
	///////////////////判断起点是否在包围盒内
	if ((minVec.x <= origin.x && origin.x < maxVec.x) &&
		(minVec.y <= origin.y && origin.y < maxVec.y) &&
		(minVec.z <= origin.z && origin.z < maxVec.z))return 1;
	//////////////////判断与每个面相交情况
	float t;
	vec3 plane;
	//与x
	if (rayDir.x != 0.0f)
	{
		if (rayDir.x > 0.0f)t = (minVec.x - origin.x) / rayDir.x;
		else t = (maxVec.x - origin.x) / rayDir.x;
		plane = origin +  rayDir*t;
		if (minVec.y < plane.y && plane.y < maxVec.y && minVec.z < plane.z && plane.z < maxVec.z)
			return 1;
	}
	//与y
	if (rayDir.y != 0.0f)
	{
		if (rayDir.y > 0.0f)t = (minVec.y - origin.y) / rayDir.y;
		else t = (maxVec.y - origin.y) / rayDir.y;
		plane = origin + rayDir * t;
		if (minVec.x < plane.x && plane.x < maxVec.x && minVec.z < plane.z && plane.z < maxVec.z)
			return 1;
	}
	//与z
	if (rayDir.z != 0.0f)
	{
		if (rayDir.z > 0.0f)t = (minVec.z - origin.z) / rayDir.z;
		else t = (maxVec.z - origin.z) / rayDir.z;
		plane = origin + rayDir * t;
		if (minVec.x < plane.x && plane.x < maxVec.x && minVec.y < plane.y && plane.y < maxVec.y)
			return 1;
	}
	///////////////////
	return 0;
}

bool AABB::IsContainAABB(const AABB& box)
{
	auto& minVec_ = box.minVec,&maxVec_ = box.maxVec;
	if (!(minVec.x<minVec_.x && maxVec.x>maxVec_.x))return 0;
	if (!(minVec.y<minVec_.y && maxVec.y>maxVec_.y))return 0;
	if (!(minVec.z<minVec_.z && maxVec.z>maxVec_.z))return 0;
	return 1;
}

vec3& AABB::GetMinVec()
{
	return minVec;
}

vec3& AABB::GetMaxVec()
{
	return maxVec;
}
