#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Clases/ParticleGenerator.h"
#include "Clases/ParticleSystem.h"
#include <iostream>
#include "Clases/GravityGenerator.h"
#include "Clases/GGenerator.h"
#include "Clases/DragGenerator.h"
#include "Clases/WhirlwindGenerator.h"
#include "Clases/ExplosionGenerator.h"

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
ContactReportCallback gContactReportCallback;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	pSystem = new ParticleSystem();
	pSystem->addForce(new GGenerator(-1, Vector3(0, -1, 0)));

	//new ParticleGenerator({ 0,40,0 }, pSystem);

	//pSystem->addParticle(new Particle(Vector3(0, 40, 0), Vector3(5, 0, 0), Vector3(0, 0, 0), 1, {1,1,0,1},1,10)); //Amarillo
	//pSystem->addParticle(new Particle(Vector3(0, 40, 0), Vector3(-5, 0, 0), Vector3(0, 0, 0), 5, { 1,0,1,1 }, 1, 10)); //Magenta
	//pSystem->addParticle(new Particle(Vector3(0, 40, 0), Vector3(0, 0, 5), Vector3(0, 0, 0), 10, { 0,1,1,1 }, 1, 10)); //Cian
	
	pSystem->addParticle(new Particle(Vector3(20, 40, 20), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 1,1,0,1 }, 1, 10)); //Amarillo
	pSystem->addParticle(new Particle(Vector3(30, 40, 30), Vector3(0, 0, 0), Vector3(0, 0, 0), 5, { 1,0,1,1 }, 1, 10)); //Magenta
	pSystem->addParticle(new Particle(Vector3(20, 40, 30), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, { 0,1,1,1 }, 1, 10)); //Cian


	//pSystem->addForce(new GGenerator(-1, Vector3(-5, 0, 0)));


	//pSystem->addForce(new GravityGenerator(Vector3(0, 60, 0), 5000000000, 10));
	
	//pSystem->addForce(new DragGenerator(10,Vector3(0,40,0),Vector3(25,25,25), Vector3(30,0,0), 1));

	
	//pSystem->addForce(new WhirlwindGenerator(10, Vector3(0, 40, 0), Vector3(100, 100, 100), 5, 1));


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
	case 'Z':
	{
		pSystem->generateProjectile(pSystem->Pistol);
		break;
	}
	case 'X':
	{
		pSystem->generateProjectile(pSystem->Artillery);
		break;
	}
	case 'C':
	{
		pSystem->generateProjectile(pSystem->FireBall);
		break;
	}
	case 'V':
	{
		pSystem->generateProjectile(pSystem->Laser);
		break;
	}
	case 'B':
	{
		pSystem->generateProjectile(pSystem->FireworkR);
		break;
	}
	case 'N':
	{
		pSystem->generateProjectile(pSystem->FireworkC);
		break;
	}
	case 'M':
	{
		pSystem->generateProjectile(pSystem->FireworkS);
		break;
	}	
	case 'K':
	{
		pSystem->addForce(new ExplosionGenerator(2, Vector3(25, 40, 25), 30, 2000, 1));
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