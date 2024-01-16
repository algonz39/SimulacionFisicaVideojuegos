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
	void score();
	void update(double t);
	void addTarget();
	PxShape* createRoof();

	bool isTarget(const PxActor* rb);
	bool isGoal(const PxActor* rb);

	int getcurrentLevel();
	int getcurrentScore();
	int getTargetScore();
	int getLostParcels();
	bool isGameOver();
	std::string getNextLevelTimer(int dec = 1);
	std::string getElapsedTime(int dec = 1);

private: 

	const int MAX_SCORES[4] = { 3, 3, 2, 2};
	std::vector<ForceGenerator*> forces;
	std::vector<ParticleGenerator*> generators;
	std::vector<PxRigidDynamic*> rigidBodys;
	PxRigidStatic* base, *goal, *house, *roof, *carretera, *camion, *trailer, *ruedaA,*ruedaB,*ruedaC,*ruedaD;
	RenderItem* baseRender;
	PxRigidDynamic* target;


	double nextLevelTimer;
	double elapsedTime;
	int currentLevel;
	int currentScore;
	int lostParcels;
	bool needTarget;
	bool gameOver;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
	PxCooking* gCooking;
	Copter* copter;


};