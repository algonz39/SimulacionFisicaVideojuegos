#include "LevelManager.h"

LevelManager::LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem) : 
	gPhysics(gPhysics), gScene(gScene), pSystem(pSystem), levelCompleted(false), currentLevel(1)
{
	loadLevel();
}

LevelManager::~LevelManager()
{
}

void LevelManager::loadLevel()
{
	switch (currentLevel)
	{
	case 1:
		rigidStatics.push_back(RigidBody::getStatic(gPhysics, gScene, { -50, 0, -50 }, CreateShape(physx::PxBoxGeometry(15, 1, 15)), { 1,1,1,1 }, PxQuat(PxPi / 4, {0,1,0})));
		rigidStatics.push_back(RigidBody::getStatic(gPhysics, gScene, { 10, 0, 10 }, CreateShape(physx::PxBoxGeometry(15, 1, 15)), { 1,1,1,1 }, PxQuat(PxPi / 4, { 0,1,0 })));

		rigidBodys.push_back(pSystem->addRigidBody(RigidBody::getDynamic(gPhysics, gScene, { 10, 7.5, 10 }, 3, 3, 3, 0.5, { 1,1,0,1 })));

		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

void LevelManager::unloadLevel()
{
	for (Particle* p : particles) {
		p->kill();
	}
	for (ForceGenerator* f : forces) {
		f;
	}
	for (Particle* p : particles) {
		p->kill();
	}
	for (Particle* p : particles) {
		p->kill();
	}
	if(currentLevel < MAX_LEVEL) {
		loadLevel();
	} 
	else {

	}
		
}

void LevelManager::score()
{
	currentLevel++;
	unloadLevel();
}

void LevelManager::die()
{
	currentLevel = 1;
	unloadLevel();
}
