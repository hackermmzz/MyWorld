#include "FireFlyRest.h"

void FireFlyRest::Enter()
{
	RestTime = FireFlyRandGenerator.rand(500, 5000);
	lastTime = gettime();
}

void FireFlyRest::Execute()
{
	if (gettime() - lastTime >= RestTime)
	SwitchState(FLYAROUND);
}

void FireFlyRest::Exit()
{

}
