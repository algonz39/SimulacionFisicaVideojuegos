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

	void move();
	void addMovement(Vector3 mov);
	void resetMovement();
	void extend(int value);
	void Copter::cableTransform();

private: 

	const float SPEED = 0.1;
	const int NUM_CHAIN = 3;

	PxRigidStatic* top1;
	PxRigidStatic* top2;
	PxRigidDynamic* magnet;

	SpringGenerator* chain;
	MagnetGenerator* magnetF;

	std::vector<RenderItem*> cable;
	std::vector<PxTransform> cableTr;
	RenderItem* shadowA;
	RenderItem* shadowB;
	PxTransform shadowTr;

	Vector3 movement;
	Vector3 magnetOffset;
	float extension;
	
	PxPhysics* gPhysics;
	PxScene* gScene;
	ParticleSystem* pSystem;
	Camera* cam;
};