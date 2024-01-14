#include "Copter.h"
#include "SpringGenerator.h"

Copter::Copter(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem)
{
	PxRigidStatic* top1 = RigidBody::getStatic(gPhysics, gScene, { 20, 45, 20 }, CreateShape(physx::PxBoxGeometry(6, 1, 2)), { 1,0,0,1 });
	PxRigidStatic* top2 = RigidBody::getStatic(gPhysics, gScene, { 20, 45, 20 }, CreateShape(physx::PxBoxGeometry(2, 1, 6)), { 1,0,0,1 });

	Particle* chainA = pSystem->addParticle(new Particle(Vector3(20, 40, 20), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 0.25,0.25,0.25,1 }, 1, 250));
	Particle* chainB = pSystem->addParticle(new Particle(Vector3(20, 35, 20), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 0.25,0.25,0.25,1 }, 1, 250));
	Particle* chainC = pSystem->addParticle(new Particle(Vector3(20, 30, 20), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 0.25,0.25,0.25,1 }, 1, 250));
	pSystem->addForce(new SpringGenerator(-1, 9, 5, chainA, { 20, 45, 20 }));
	pSystem->addForce(new SpringGenerator(-1, 9, 5, chainA, chainB));
	pSystem->addForce(new SpringGenerator(-1, 9, 5, chainB, chainC));
}

Copter::~Copter()
{

}

void Copter::move(Vector3 movement)
{
	PxTransform newPose{ top1->getGlobalPose().p += movement };
	top1->setGlobalPose(newPose);
	top2->setGlobalPose(newPose);
}
