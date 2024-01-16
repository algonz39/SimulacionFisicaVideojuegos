#include "LevelManager.h"
#include "DragGenerator.h"
#include "WhirlwindGenerator.h"
#include "BouyancyForceGenerator.h"

LevelManager::LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Copter* copter) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem),
	copter(copter), levelCompleted(-1), needTarget(false), currentLevel(4), currentScore(0), base(nullptr), goal(nullptr)
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
		generators.push_back( new ParticleGenerator({ -20, 10, -10 }, pSystem, false, { 1, { 0,1,1,1 }, 0.5, 2.0, Sphere } , 0.2, 7, 10));
		forces.push_back(pSystem->addForce(new DragGenerator(-1, { -20, 10, -20 }, { 20, 40, 20 }, { 30,0,-10 }, 10)));
		addTarget();
		break;
	case 3:
		generators.push_back(new ParticleGenerator({ -20, 10, -20 }, pSystem, false, { 1, { 0,1,1,1 }, 0.5, 4.0, Sphere }, 0.4, 20, 0.5));
		forces.push_back(pSystem->addForce(new WhirlwindGenerator(-1, { -20,10,-20 }, { 20,40,20 }, 2, 5)));
		addTarget();
		break;
	case 4:
		base->release();
		//DeregisterRenderItem(RigidBody::staticRender.at(base));
		forces.push_back(pSystem->addForce(new BouyancyForceGenerator(-1,{ 10, 0, 10 },5,100,2)));
		addTarget();
		break;
	case 5:
		base = RigidBody::getStatic(gPhysics, gScene, { 10, 0, 10 }, CreateShape(physx::PxBoxGeometry(20, 1, 20)), { 1,1,1,1 }, PxQuat(PxPi / 4, { 0,1,0 }));
		generators.push_back(new ParticleGenerator({ -20, 10, -20 }, pSystem, false, { 1, { 0,1,1,1 }, 0.5, 4.0, Sphere }, 0.4, 20, 0.5));
		forces.push_back(pSystem->addForce(new WhirlwindGenerator(-1, { -20,10,-20 }, { 20,40,20 }, 2, 5)));
		addTarget();
		break;
	case 6:
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
	for (ParticleGenerator* gen : generators) {
		gen->kill();
	}
	generators.clear();
	for (ForceGenerator* f : forces) {
		f->kill();
	}
	forces.clear();
	copter->reset();
	levelCompleted = -1;
	currentScore = 0;
	loadLevel();
}

void LevelManager::score()
{
	currentScore++;
	new ParticleGenerator({ -75, 0, -180 }, pSystem, Firework::Fireworks, 0.015, 10, 5, 3);
	new ParticleGenerator({ -180, 0, -75 }, pSystem, Firework::Fireworks, 0.015, 10, 5, 3);
	target->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	target->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	target->clearForce();
	target = nullptr;
	copter->setTarget(target);
	if (currentScore < MAX_SCORES[currentLevel - 1]) {
		needTarget = true;
	}
	else {
		currentLevel++;
		levelCompleted = 5;
	}
}

void LevelManager::update(double t)
{
	for (auto iter = rigidBodys.begin(); iter != rigidBodys.end();) {
		PxRigidDynamic* rb = *iter;
		if (rb->getGlobalPose().p.y < -20) {
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
	PxMaterial* mat = gPhysics->createMaterial(1.0f,1.0f,0.4f);
	rigidBodys.push_back(target = pSystem->addRigidBody(
		RigidBody::getDynamic(gPhysics, gScene, {10, 6, 10 }, rnd->getRandomShape(mat), rnd->generate(1)/1.25, rnd->getRandomColor())));
	copter->setTarget(target);
	needTarget = false;
}

bool LevelManager::isTarget(const PxActor* rb) {
	return rb == target;
}

bool LevelManager::isGoal(const PxActor* rb) {
	return rb == goal;
}