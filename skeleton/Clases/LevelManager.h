#pragma once
#include "Rigidbody.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "RigidBodyGenerator.h"
#include "ForceGenerator.h"

class LevelManager 
{
public:
	LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem);
	virtual ~LevelManager();

	void loadLevel();
	void unloadLevel();
	void score();
	void die();

private: 

	const int MAX_LEVEL = 3;
	std::vector<Particle*> particles;
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;
	std::vector<PxRigidActor*> rigidBodys;
	std::vector<PxRigidStatic*> rigidStatics;

	bool levelCompleted;
	int currentLevel;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;


};