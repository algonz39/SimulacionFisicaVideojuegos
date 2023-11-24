#pragma once
#include "Particle.h"
#include <vector>

class ForceGenerator {
public:
	ForceGenerator(double lTime = 5);
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle) {}
	bool updateLifeTime(double t);

protected:
	double lifeTime;
	double time;
};