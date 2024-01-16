#pragma once 
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "Rigidbody.h"
#include "Particle.h"
#include "Random.h"
#include <vector>
#include <unordered_map>

class ParticleGenerator;
class ForceGenerator;
class RigidBodyGenerator;


class ParticleSystem {
public:
	//enum ProjectileType {
	//	Pistol,
	//	Artillery,
	//	FireBall,
	//	Laser,
	//	Fireworks,
	//	FireworkR,
	//	FireworkC,
	//	FireworkS,
	//	LastEnum
	//};

	ParticleSystem(PxPhysics* gPhysics, PxScene* gScene);
	~ParticleSystem();
	//void generateProjectile(ProjectileType type);
	void update(double t);
	Particle* addParticle(Particle* p);
	ParticleGenerator* addGenerator(ParticleGenerator* p);
	RigidBodyGenerator* addRBGenerator(RigidBodyGenerator* p);
	ForceGenerator* addForce(ForceGenerator* f);
	PxRigidDynamic* addRigidBody(std::pair<PxRigidDynamic*, RenderItem*>);
	void releaseRb(PxRigidDynamic* rb);
	bool maxParticles();
	bool maxRB();
	Random* getRand();
	PxPhysics* getPhysics();
	PxScene* getScene();

private: 
	PxPhysics* gPhysics;
	PxScene* gScene;
	std::vector<Particle*> particles;
	std::vector<Particle*> particlesToAdd;
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;
	std::vector<RigidBodyGenerator*> rbGenerators;
	std::vector<PxRigidDynamic*> rigidBodys;
	std::unordered_map<PxRigidDynamic*, RenderItem*> renderItems;

	const int MAX_PARTICLES = 1000;
	const int MAX_RB = 100;

	int nParticles, nGenerators, nForces, nRigidBodys;
	Camera* cam;
	Random* rand;
};