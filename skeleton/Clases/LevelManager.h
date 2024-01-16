#pragma once
#include "Rigidbody.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "Copter.h"

class LevelManager 
{
public:
	LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Copter* copter);
	virtual ~LevelManager();

	void loadLevel();
	void unloadLevel();
	void score();
	void update(double t);
	void addTarget();
	bool isTarget(const PxActor* rb);
	bool isGoal(const PxActor* rb);

private: 

	const int MAX_LEVEL = 5;
	const int MAX_SCORES[5] = { 2, 2, 3, 3, 4};
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;
	std::vector<PxRigidDynamic*> rigidBodys;
	PxRigidStatic* base, *goal;
	PxRigidDynamic* target;


	double levelCompleted;
	bool needTarget;
	int currentLevel;
	int currentScore;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
	Copter* copter;


};