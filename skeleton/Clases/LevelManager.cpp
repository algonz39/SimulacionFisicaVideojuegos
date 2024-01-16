#include "LevelManager.h"
#include "DragGenerator.h"

LevelManager::LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Copter* copter) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem),
	copter(copter), levelCompleted(-1), needTarget(false), currentLevel(1), currentScore(0), base(nullptr), goal(nullptr)
{
	base = RigidBody::getStatic(gPhysics, gScene, { 10, 0, 10 }, CreateShape(physx::PxBoxGeometry(20, 1, 20)), { 1,1,1,1 }, PxQuat(PxPi / 4, { 0,1,0 }));
	goal = RigidBody::getStatic(gPhysics, gScene, { -50, 0, -50 }, CreateShape(physx::PxBoxGeometry(20, 1, 20)), { 1,1,1,1 }, PxQuat(PxPi / 4, { 0,1,0 }));
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

		addTarget();

		break;
	case 2:
		generators.push_back( new ParticleGenerator({ -20, 0, -20 }, pSystem, false, ParticleData(), 0.1, 10, 15));
		forces.push_back(pSystem->addForce(new DragGenerator(-1, { -20,0,-20 }, { 40,30,40 }, { 30,0,0 }, 10)));
		addTarget();

		break;
	case 3:
		break;
	default:
		break;
	}
}

void LevelManager::unloadLevel()
{
	for (PxRigidDynamic* rb : rigidBodys) {
		pSystem->releaseRb(rb);
	}
	rigidBodys.clear();
	copter->reset();
	levelCompleted = -1;
	currentScore = 0;
	loadLevel();
}

void LevelManager::score()
{
	currentScore++;
	new ParticleGenerator({ -50, 0, -120 }, pSystem, Firework::Fireworks, 0.015, 10, 5, 3);
	new ParticleGenerator({ -120, 0, -50 }, pSystem, Firework::Fireworks, 0.015, 10, 5, 3);
	if (currentScore < MAX_SCORES[currentLevel - 1]) {
		target = nullptr;
		needTarget = true;
	}
	else {
		target = nullptr;
		currentLevel++;
		levelCompleted = 5;
	}
}

void LevelManager::update(double t)
{
	for (auto iter = rigidBodys.begin(); iter != rigidBodys.end();) {
		PxRigidDynamic* rb = *iter;
		if (rb->getGlobalPose().p.y < -10) {
			iter = rigidBodys.erase(iter);
			pSystem->releaseRb(rb);
			if (isTarget(rb)) {
				needTarget = true;
				target = nullptr;
			}
		}
		else {
			++iter;
		}
	}
	if (needTarget) addTarget();
	if (levelCompleted > -1) {
		levelCompleted -= t;
		if (levelCompleted < 0) unloadLevel();
	}
}

void LevelManager::addTarget()
{
	Random* rnd = pSystem->getRand();
	PxMaterial* mat = gPhysics->createMaterial(0.8f,0.8f,0.6f);;
	rigidBodys.push_back(target = pSystem->addRigidBody(
		RigidBody::getDynamic(gPhysics, gScene, {10, 6, 10 }, rnd->getRandomShape(mat), rnd->generate(1), rnd->getRandomColor())));
	needTarget = false;
}

bool LevelManager::isTarget(const PxActor* rb) {
	return rb == target;
}

bool LevelManager::isGoal(const PxActor* rb) {
	return rb == goal;
}
