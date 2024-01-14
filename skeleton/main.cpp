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


#pragma region Project

	pSystem = new ParticleSystem(gPhysics, gScene);
	RigidBody::getStatic(gPhysics, gScene, { -20, 0, -20 }, CreateShape(physx::PxBoxGeometry(200, 1, 200)), {1,1,1,1});
	pSystem->addForce(new GGenerator(-1, Vector3(0, -9.8, 0)));

	new Copter(gPhysics,gScene,pSystem);

	//new RigidBodyGenerator({-20,40,-20},pSystem,0.05,10,10);
	//pSystem->addForce(new WhirlwindGenerator(25, Vector3(-20, 40, -20), Vector3(100, 100, 100), 5, 1));
#pragma endregion

#pragma region P4

	//Muelle
	//Particle* am = pSystem->addParticle(new Particle(Vector3(20, 40, 20), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 1,1,0,1 }, 1, 10)); //Amarillo
	//Particle* ma = pSystem->addParticle(new Particle(Vector3(30, 40, 30), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 1,0,1,1 }, 1, 10)); //Magenta
	//pSystem->addForce(new SpringGenerator(-1,5,5,am, ma));

	//Muelle estatico
	//Particle* gr = pSystem->addParticle(new Particle(Vector3(0, 40, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, { 0,1,0,1 }, 1, 25)); //Green
	//Particle* top = pSystem->addParticle(new Particle(Vector3(0, 50, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, { 1,1,1,1 }, 1, 25)); //Gray
	//pSystem->addForce(new GGenerator(-1, Vector3(0, -9.8, 0)))->addExcluded(top);
	//pSystem->addForce(new SpringGenerator(-1, 10, 5, gr, Vector3(0,50,0)));
	//pSystem->addForce(new DragGenerator(-1,Vector3(0,50,0), Vector3(50, 50, 50), Vector3(50,0,0), 1))->addExcluded(top);

	//Slinky
	//Particle* am = pSystem->addParticle(new Particle(Vector3(10, 50, 10), Vector3(0, 0, -5), Vector3(0, 0, 0), 5, { 1,1,0,1 }, 1, 50)); //Amarillo
	//Particle* ma = pSystem->addParticle(new Particle(Vector3(10, 45, 10), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 1,0,1,1 }, 1, 50)); //Magenta
	//Particle* cy = pSystem->addParticle(new Particle(Vector3(10, 40, 10), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 0,1,1,1 }, 1, 50)); //Cian
	//Particle* ro = pSystem->addParticle(new Particle(Vector3(10, 35, 10), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 1,0,0,1 }, 1, 50)); //Rojo
	//Particle* ve = pSystem->addParticle(new Particle(Vector3(10, 30, 10), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 0,1,0,1 }, 1, 50)); //Verde
	//pSystem->addForce(new SpringGenerator(-1, 5, 5, am, ma));
	//pSystem->addForce(new SpringGenerator(-1, 5, 5, ma, cy));
	//pSystem->addForce(new SpringGenerator(-1, 5, 5, cy, ro));
	//pSystem->addForce(new SpringGenerator(-1, 5, 5, ro, ve));


	//Flotacion
	//red = pSystem->addParticle(new Particle(Vector3(-20, 40, -20), Vector3(0, 0, 0), Vector3(0, 0, 0), 7000, { 1,0,0,1 }, 10, 1000, Cube)); //Red
	//Particle* sea = pSystem->addParticle(new Particle(Vector3(-20, 40, -20), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 0,0,1,1 }, 30, 1000, Plane)); //Sea
	//pSystem->addForce(new BouyancyForceGenerator(-1, sea, 10, 10, 1000));
	//pSystem->addForce(new GGenerator(-1, Vector3(0, -9.8, 0)))->addExcluded(sea);


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
		copter->move(Vector3(-10, 0, -10));
		break;
	}
	case 'A':
	{
		copter->move(Vector3(-10, 0, 10));
		break;
	}
	case 'S':
	{
		copter->move(Vector3(10, 0, 10));
		break;
	}

	case 'D':
	{
		copter->move(Vector3(10, 0, -10));
		break;
	}
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
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