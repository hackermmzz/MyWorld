#include"FireFlyBorn.h"
FireFlyBorn::FireFlyBorn(vec3& currentPos_,float&speed_)
	:speed(&speed_),currentPos(&currentPos_)
{
}
void FireFlyBorn::Enter()
{
	static float div = 10.0;
	auto& rand = FireFlyRandGenerator;
	float x = rand.rand(0, 8) / div*rand.rand(0,1)?-1:1;
	float y = rand.rand(0, 1) ? (1* rand.rand(0, 8)/div) : (-1* rand.rand(0,5)/div);
	float z = rand.rand(0, 8) / div * rand.rand(0, 1) ? -1 : 1;
	vec3 offset= vec3(x, y, z);
	targetPos = *currentPos + offset;
	speed_v = offset**speed;
	lasttime = gettime();
}

void FireFlyBorn::Execute()
{
	static auto minus= std::numeric_limits<float>::epsilon();
	auto time = gettime();
	auto deltaTime = (time - lasttime) / 1000.0;
	lasttime = time;
	vec3 offset= speed_v*deltaTime;
	bool check = FireFlyCheck(*currentPos + offset);
	if (!check)*currentPos += offset;
	if (check||
		abs(currentPos->x)>abs(targetPos.x)||
		abs(currentPos->y)>abs(targetPos.y)||
		abs(currentPos->z)>abs(targetPos.z)
		)SwitchState(REST);
}

void FireFlyBorn::Exit()
{

}
