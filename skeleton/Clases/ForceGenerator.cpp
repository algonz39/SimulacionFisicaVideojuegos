#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(double lTime) : lifeTime(lTime), time(0)
{
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::updateLifeTime(double t)
{
	if (lifeTime < 0) return false;
	time += t;
	return (time > lifeTime);
}
