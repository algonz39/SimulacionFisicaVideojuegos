#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include <vector>

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, double Prob = 0.45, double Velocity = 5);
	~ParticleGenerator();
	void generate(double t);


private: 
	ParticleSystem* sys;
	Vector3 pos;
	double genProb;
	double velocity;
	Vector3 getRandomVelocity();
};