#pragma once 
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "Particle.h"
#include "Random.h"
#include <vector>

class ParticleGenerator;
class ForceGenerator;


class ParticleSystem {
public:
	enum ProjectileType {
		Pistol,
		Artillery,
		FireBall,
		Laser,
		Fireworks,
		FireworkR,
		FireworkC,
		FireworkS,
		LastEnum
	};

	ParticleSystem();
	~ParticleSystem();
	void generateProjectile(ProjectileType type);
	void update(double t);
	Vector3 getGravity();
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* p);
	void addForce(ForceGenerator* f);
	bool maxParticles();
	Random* getRand();

private: 
	std::vector<Particle*> particles;
	std::vector<Particle*> particlesToAdd;
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;

	const int MAX_PARTICLES = 1000;

	int nParticles, nGenerators, nForces;
	Camera* cam;
	Random* rand;
};