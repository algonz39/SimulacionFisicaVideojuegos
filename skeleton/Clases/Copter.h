#pragma once
#include "Rigidbody.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "RigidBodyGenerator.h"
#include "ForceGenerator.h"

class Copter 
{
public:
	Copter(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem);
	virtual ~Copter();

	void move(Vector3 movement);
private: 

	PxRigidStatic* top1;
	PxRigidStatic* top2;

	std::vector<Particle*> chainP;
	std::vector<ForceGenerator*> chainF;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
};