#pragma once 
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "Particle.h"
#include <vector>

class ParticleGenerator;

class ParticleSystem {
public:
	enum ProjectileType {
		Pistol,
		Artillery,
		FireBall,
		Laser,
		LastEnum
	};
	ParticleSystem();
	~ParticleSystem();
	void generateProjectile(ProjectileType type);
	void updateParticles(double t);
	Vector3 getGravity();
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* p);
	bool maxParticles();

private: 
	std::vector<Particle*> particles;
	std::vector<ParticleGenerator*> generators;

	const int MAX_PARTICLES = 100;

	int nParticles, nGenerators;
	Camera* cam;
};