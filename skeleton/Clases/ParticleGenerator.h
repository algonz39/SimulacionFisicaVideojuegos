#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include "Firework.h"
#include <vector>
#include <random>

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, bool Gausian = false, ParticleData Data = ParticleData(),  double Prob = 0.45, double Velocity = 10, double Radius = 5, float duration = -1);
	ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, Firework::FireType type,  double Prob = 0.45, double Velocity = 10, double Radius = 5, float duration = -1);
	~ParticleGenerator();
	bool generate(double t);


protected: 
	ParticleSystem* sys;
	Vector3 pos;
	ParticleData data;
	Firework::FireType type;
	double genProb;	
	double velocity;
	double radius;
	float duration;
	bool gausian;

	std::vector<Particle*> particles;
};