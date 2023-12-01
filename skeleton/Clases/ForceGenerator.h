#pragma once
#include "Particle.h"
#include <vector>
#include <unordered_set>

class ForceGenerator {
public:
	ForceGenerator(double lTime = 5);
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle) {}
	bool updateLifeTime(double t);
	void addExcluded(Particle* p);

protected:
	double lifeTime;
	double time;
	std::unordered_set<Particle*> excluded;
};