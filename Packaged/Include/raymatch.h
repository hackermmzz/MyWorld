#ifndef RAYMATCH_H
#define RAYMATCH_H
#include"Include.h"
#include"vec.hpp"
//////////////////////////////////////////////////
struct Ray {
    vec3 origin;
    vec3 direction;
    Ray(const vec3& origin, const vec3& direction);
    Ray(){}
};
//////////////////////////////////////////////////
class RayMatch
{
private:
    Ray ray;
    vec3 CurrentPos;
public:
    RayMatch(const vec3&origin,const vec3&direction);
    const vec3 &GetRay();
    void Step(float scale);
    float Distance();
    ~RayMatch();
};

#endif // RAYMATCH_H
