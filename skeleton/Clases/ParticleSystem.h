#pragma once 
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "Particle.h"
#include "Random.h"
#include <vector>

class ParticleGenerator;

class ParticleSystem {
public:
	enum ProjectileType {
		Pistol,
		Artillery,
		FireBall,
		Laser,
		FireworkR,
		FireworkC,
		FireworkS,
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
	Random* getRand();

private: 
	std::vector<Particle*> particles;
	std::vector<Particle*> particlesToAdd;
	std::vector<ParticleGenerator*> generators;

	const int MAX_PARTICLES = 1000;

	int nParticles, nGenerators;
	Camera* cam;
	Random* rand;
};