#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "ParticleSystem.h"
#include <vector>
#include <random>

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, bool Gausian = false, ParticleData Data = ParticleData(),  double Prob = 0.45, double Velocity = 10, double Radius = 5);
	~ParticleGenerator();
	void generate(double t);


protected: 
	ParticleSystem* sys;
	Vector3 pos;
	ParticleData data;
	double genProb;	
	double velocity;
	double radius;
	bool gausian;

	std::random_device rd{};
	std::mt19937 gen{rd()};
	
	std::uniform_real_distribution<float> uni{-1.0,1.0};
	std::normal_distribution<float> norm{ 0.0, 1.0 };

	std::vector<Particle*> particles;

	Vector3 getRandomVector();
};