#pragma once
#include "Rigidbody.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "Copter.h"

class LevelManager 
{
public:
	LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, PxCooking* gCooking, Copter* copter);
	virtual ~LevelManager();

	void loadLevel();
	void unloadLevel();
	void gameOver();
	void score();
	void update(double t);
	void addTarget();
	PxShape* createRoof();

	bool isTarget(const PxActor* rb);
	bool isGoal(const PxActor* rb);

	int getcurrentLevel();
	int getcurrentScore();
	int getTargetScore();
	double getNextLevelTimer();

private: 

	const int MAX_LEVEL = 5;
	const int MAX_SCORES[5] = { 3, 3, 2, 2, 3};
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;
	std::vector<PxRigidDynamic*> rigidBodys;
	PxRigidStatic* base, *goal, *house, *roof, *carretera, *camion, *trailer, *ruedaA,*ruedaB,*ruedaC,*ruedaD;
	RenderItem* baseRender;
	PxRigidDynamic* target;


	double nextLevelTimer;
	bool needTarget;
	int currentLevel;
	int currentScore;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
	PxCooking* gCooking;
	Copter* copter;


};