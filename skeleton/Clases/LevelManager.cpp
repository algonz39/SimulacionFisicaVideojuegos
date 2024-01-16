#include "LevelManager.h"
#include "DragGenerator.h"
#include "WhirlwindGenerator.h"
#include "BouyancyForceGenerator.h"
#include <sstream>
#include <iomanip>

LevelManager::LevelManager(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, PxCooking* gCooking, Copter* copter) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem), 
	gCooking(gCooking),	copter(copter), nextLevelTimer(-1), needTarget(false), currentLevel(1), currentScore(0), elapsedTime(0), lostParcels(0), gameOver(false)
{
	std::tie(base, baseRender) = 
		RigidBody::getStaticandRender(gPhysics, gScene, { 10, 0, 10 }, CreateShape(physx::PxBoxGeometry(20, 1, 20)), { 0.4,0.4,0.4,1 }, PxQuat(PxPi / 4, { 0,1,0 }));

	goal = RigidBody::getStatic(gPhysics, gScene, { -70, 0, -70 }, CreateShape(physx::PxBoxGeometry(20, 1, 27)), { 0.34,0.51,0.34,1 }, PxQuat(PxPi / 4, { 0,1,0 }));

	house = RigidBody::getStatic(gPhysics, gScene, { -80 , 8, -80 }, CreateShape(physx::PxBoxGeometry(12, 8, 12)), { 0.8,0.5,0.4,1 }, PxQuat(PxPi / 4, { 0,1,0 }));

	roof = RigidBody::getStatic(gPhysics, gScene, { -80 , 16, -80 }, createRoof(), {0.7,0.4,0.4,1}, PxQuat(PxPi / 4, {0,1,0}));


	carretera = RigidBody::getStatic(gPhysics, gScene, { -11.5, 0, 31.5 }, CreateShape(physx::PxBoxGeometry(10.5, 1, 20)), { 0.15,0.15,0.15,1 }, PxQuat(PxPi / 4, { 0,1,0 }));

	camion = RigidBody::getStatic(gPhysics, gScene, { -2, 11, 40 }, CreateShape(physx::PxBoxGeometry(6, 5, 5)), { 0.8,0.8,0.8,1 }, PxQuat(PxPi / 4, { 0,1,0 }));
	trailer = RigidBody::getStatic(gPhysics, gScene, { -14.5 , 13, 27.5 }, CreateShape(physx::PxBoxGeometry(8, 8, 14)), { 0.1,0.6,0.9,1 }, PxQuat(PxPi / 4, { 0,1,0 }));
	ruedaA = RigidBody::getStatic(gPhysics, gScene, { -5, 3, 29 }, CreateShape(physx::PxSphereGeometry(3)), { 0,0,0,1 });
	ruedaB = RigidBody::getStatic(gPhysics, gScene, { -13, 3, 37 }, CreateShape(physx::PxSphereGeometry(3)), { 0,0,0,1 });
	ruedaC = RigidBody::getStatic(gPhysics, gScene, { -17, 3, 17 }, CreateShape(physx::PxSphereGeometry(3)), { 0,0,0,1 });
	ruedaD = RigidBody::getStatic(gPhysics, gScene, { -25, 3, 25 }, CreateShape(physx::PxSphereGeometry(3)), { 0,0,0,1 });

	
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
		base->release();
		DeregisterRenderItem(baseRender);
		forces.push_back(pSystem->addForce(new BouyancyForceGenerator(-1, { 10, 0, 10 }, 4, 25, 1)));
		forces[0]->addExcluded(copter->getMagnet());
		addTarget();
		break;
	case 3:
		std::tie(base, baseRender) =
			RigidBody::getStaticandRender(gPhysics, gScene, { 10, 0, 10 }, CreateShape(physx::PxBoxGeometry(20, 1, 20)), { 1,1,1,1 }, PxQuat(PxPi / 4, { 0,1,0 }));

		generators.push_back( new ParticleGenerator({ -30, 10, -20 }, pSystem, false, { 1, { 0,1,1,1 }, 0.5, 2.0, Sphere } , 0.2, 7, 10));
		forces.push_back(pSystem->addForce(new DragGenerator(-1, { -30, 10, -30 }, { 30, 50, 30 }, { 30,0,-10 }, 10)));
		addTarget();
		break;
	case 4:
		generators.push_back(new ParticleGenerator({ -30, 10, -30 }, pSystem, false, { 1, { 0,1,1,1 }, 0.5, 4.0, Sphere }, 0.4, 20, 0.5));
		forces.push_back(pSystem->addForce(new WhirlwindGenerator(-1, { -30,10,-30 }, { 30,70,30 }, 2, 5)));
		addTarget();
		break;
	case 5:
		gameOver = true;
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
	nextLevelTimer = -1;
	currentScore = 0;
	loadLevel();
}

void LevelManager::score()
{
	currentScore++;
	new ParticleGenerator({ -75, 0, -150 }, pSystem, Firework::Fireworks, 0.05, 10, 3, 0.75);
	new ParticleGenerator({ -150, 0, -75 }, pSystem, Firework::Fireworks, 0.05, 10, 3, 0.75);
	target->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	target->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	target->clearForce();
	target = nullptr;
	copter->setTarget(target);
	if (currentScore < MAX_SCORES[currentLevel - 1]) {
		needTarget = true;
	}
	else {
		nextLevelTimer = 3.5;
	}
}

void LevelManager::update(double t)
{

	for (auto iter = rigidBodys.begin(); iter != rigidBodys.end();) {
		PxRigidDynamic* rb = *iter;
		if (rb->getGlobalPose().p.y < -20) {
			iter = rigidBodys.erase(iter);
			pSystem->releaseRb(rb);
			lostParcels++;
			if (isTarget(rb)) {
				needTarget = true;
				target = nullptr;
			}
			else {
				--currentScore;
				if (currentScore < MAX_SCORES[currentLevel - 1])
				{
					nextLevelTimer = -1;
					if(target == nullptr) needTarget = true;
				}
			}
		}
		else {
			++iter;
		}
	}
	if (needTarget) addTarget();
	if (nextLevelTimer > -1) {
		nextLevelTimer -= t;
		if (nextLevelTimer < 0)
		{
			currentLevel++;
			unloadLevel();
		}
	}
	else if(!gameOver)elapsedTime += t;

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

PxShape* LevelManager::createRoof() {
	const PxVec3 convexVerts[] = { PxVec3(12,0,12),PxVec3(12,0,-12),PxVec3(-12,0,12),PxVec3(-12,0,-12),PxVec3(0,8,12),PxVec3(0,8,-12)};

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = 6;
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = convexVerts;
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

	PxDefaultMemoryOutputStream buf;
	PxConvexMeshCookingResult::Enum result;
	if (!gCooking->cookConvexMesh(convexDesc, buf, &result))
		return NULL;
	PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	PxConvexMesh* convexMesh = gPhysics->createConvexMesh(input);

	return CreateShape(PxConvexMeshGeometry(convexMesh));

}


bool LevelManager::isTarget(const PxActor* rb) {
	return rb == target;
}

bool LevelManager::isGoal(const PxActor* rb) {
	return rb == goal;
}

int LevelManager::getcurrentLevel() {
	return currentLevel;
} 

int LevelManager::getcurrentScore() {
	return currentScore;
};

int LevelManager::getTargetScore() {
	return MAX_SCORES[currentLevel-1];
}

int LevelManager::getLostParcels() {
	return lostParcels;
}

bool LevelManager::isGameOver() {
	return gameOver;
}

std::string LevelManager::getNextLevelTimer(int dec) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << nextLevelTimer;
	return ss.str();
}

std::string LevelManager::getElapsedTime(int dec) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(dec) << elapsedTime;
	return ss.str();
}

