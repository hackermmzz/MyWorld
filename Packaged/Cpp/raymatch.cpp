#include "Include/raymatch.h"
RayMatch::RayMatch(const vec3 &position, const vec3 &direction_)
{
    ray.origin=position;
    CurrentPos=ray.origin;
    ray.direction=direction_.normalize();
}
const vec3&RayMatch::GetRay()
{
    return CurrentPos;
}

void RayMatch::Step(float scale)
{
    CurrentPos+=ray.direction*scale;
}

float RayMatch::Distance()
{
    return (CurrentPos-ray.origin).distance();
}

RayMatch::~RayMatch()
{

}
