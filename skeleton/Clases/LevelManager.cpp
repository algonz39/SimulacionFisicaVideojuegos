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
