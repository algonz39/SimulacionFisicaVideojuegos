#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Clases/ParticleGenerator.h"
#include "Clases/RigidBodyGenerator.h"
#include "Clases/ParticleSystem.h"
#include <iostream>
#include "Clases/GravityGenerator.h"
#include "Clases/GGenerator.h"
#include "Clases/DragGenerator.h"
#include "Clases/WhirlwindGenerator.h"
#include "Clases/ExplosionGenerator.h"
#include "Clases/SpringGenerator.h"
#include "Clases/BouyancyForceGenerator.h"
#include "Clases/Copter.h"
#include "Clases/LevelManager.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = nullptr;
PxPhysics*				gPhysics	= nullptr;


PxMaterial*				gMaterial	= nullptr;

PxPvd*                  gPvd        = nullptr;

PxDefaultCpuDispatcher*	gDispatcher = nullptr;
PxScene*				gScene      = nullptr;
ParticleSystem*			pSystem	    = nullptr;
Copter*					copter		= nullptr;
LevelManager*			lvlManager  = nullptr;

ContactReportCallback gContactReportCallback;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	pSystem = new ParticleSystem(gPhysics, gScene);


#pragma region Project

	copter = new Copter(gPhysics, gScene, pSystem, Vector3{15,45,15});
	lvlManager = new LevelManager(gPhysics, gScene, pSystem, copter);
	//new RigidBodyGenerator({-20,40,-20},pSystem,0.05,10,10);
	//pSystem->addForce(new WhirlwindGenerator(25, Vector3(-20, 40, -20), Vector3(100, 100, 100), 5, 1));
#pragma endregion

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	pSystem->update(t);
	copter->move();
	lvlManager->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete pSystem;
	delete copter;
	delete lvlManager;

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);


	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'W':
	{
		copter->addMovement(Vector3(-1, 0, -1));
		break;
	}
	case 'A':
	{
		copter->addMovement(Vector3(-1, 0, 1));
		break;
	}
	case 'S':
	{
		copter->addMovement(Vector3(1, 0, 1));
		break;
	}

	case 'D':
	{
		copter->addMovement(Vector3(1, 0, -1));
		break;
	}
	case ' ': {
		copter->resetMovement();
		break;
	}
	case 'Q':
	{
		copter->extend(-1);
		break;
	}

	case 'E':
	{
		copter->extend(1);
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	if(lvlManager->isTarget(actor1) && lvlManager->isGoal(actor2)) {
		lvlManager->score();
	}
	else if (lvlManager->isTarget(actor2) && lvlManager->isGoal(actor1)) {
		lvlManager->score();
	}
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}