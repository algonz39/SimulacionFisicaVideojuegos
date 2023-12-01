#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(double lTime) : lifeTime(lTime), time(0), excluded(std::unordered_set<Particle*>())
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

void ForceGenerator::addExcluded(Particle* p)
{
	excluded.insert(p);
}
