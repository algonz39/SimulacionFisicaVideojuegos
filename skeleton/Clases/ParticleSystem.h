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

private: 
	std::vector<Particle*> particles;
	std::vector<ParticleGenerator*> generators;


	int nParticles, nGenerators;
	Camera* cam;
};