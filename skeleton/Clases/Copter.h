#pragma once
#include "Rigidbody.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "RigidBodyGenerator.h"
#include "SpringGenerator.h"
#include "MagnetGenerator.h"

class Copter 
{
public:
	Copter(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Vector3 pos);
	virtual ~Copter();

	void move(Vector3 movement);
	void extend(int value);
private: 

	PxRigidStatic* top1;
	PxRigidStatic* top2;
	PxRigidDynamic* magnet;

	SpringGenerator* chain;
	MagnetGenerator* magnetF;

	Vector3 magnetOffset;

	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
	Camera* cam;
};