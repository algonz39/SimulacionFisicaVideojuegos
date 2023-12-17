#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include <vector>
#include <random>

class RigidBodyGenerator
{
public:
	RigidBodyGenerator(Vector3 Pos, ParticleSystem* Sys,  double Prob = 0.45, double Velocity = 10, double Radius = 5);
	~RigidBodyGenerator();
	void generate(double t);


protected: 
	ParticleSystem* sys;
	Vector3 pos;
	ParticleData data;
	double genProb;	
	double velocity;
	double radius;

};