#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include <vector>
#include <random>

class ForceGenerator
{
public:
	ForceGenerator();
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle);
};