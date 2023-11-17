#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include <vector>
#include <random>

class ForceGenerator
{
public:
	ForceGenerator(double lTime = 5);
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle);
	bool updateLifeTime(double t);

protected:
	double lifeTime;
	double time;
};