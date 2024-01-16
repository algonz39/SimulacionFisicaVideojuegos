#include "Copter.h"
#include "SpringGenerator.h"
#include <PxPhysicsAPI.h>

Copter::Copter(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Vector3 pos) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem),
	ogPos(pos), magnetOffset(Vector3(0, 10, 0)), movement(0,0,0), extension(0)
{
	cam = GetCamera();

	top1 = RigidBody::getStatic(gPhysics, gScene, { pos }, CreateShape(physx::PxBoxGeometry(6, 1, 2)), { 1,0.55,0,1 });
	top2 = RigidBody::getStatic(gPhysics, gScene, { pos }, CreateShape(physx::PxBoxGeometry(2, 1, 6)), { 1,0.55,0,1 });
	magnet = pSystem->addRigidBody(RigidBody::getDynamic(gPhysics, gScene, pos - magnetOffset, 1, 0.5, 1, 30, { 0.1,0.1,0.1,1 }));

	pSystem->addForce(chain = new SpringGenerator(-1, 100, 10, pos - magnetOffset, magnet));
	pSystem->addForce(magnetF = new MagnetGenerator(magnet, 120, -1 ));
	cableTr = std::vector<PxTransform>(NUM_CHAIN);
	for (int i = 0; i < NUM_CHAIN; i++) {
		cableTr.at(i) = PxTransform(0, 0, 0);
		cable.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &cableTr.at(i), {0,0,0,1}));
	}
	cableTransform();

	shadowTr = PxTransform(pos.x, 1,pos.z);
	shadowA = new RenderItem(CreateShape(physx::PxBoxGeometry(5,0.01,1)), &shadowTr, {0,0,0,1});
	shadowB = new RenderItem(CreateShape(physx::PxBoxGeometry(1,0.01,5)), &shadowTr, {0,0,0,1});

}

Copter::~Copter()
{
	for (auto& a : cable) {
		DeregisterRenderItem(a);
	}
	DeregisterRenderItem(shadowA);
	DeregisterRenderItem(shadowB);

}

void Copter::move()
{
	PxTransform newPose{ top1->getGlobalPose().p += movement * SPEED };
	chain->setFPos(newPose.p - magnetOffset);
	top1->setGlobalPose(newPose);
	top2->setGlobalPose(newPose);
	cam->setEye((movement* SPEED));

	magnetOffset.y += extension * 0.15;
	if (magnetOffset.y < 5) magnetOffset.y = 5;
	else if (magnetOffset.y > 35) magnetOffset.y = 35;
	chain->setFPos(top1->getGlobalPose().p - magnetOffset);
	magnet->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));

	cableTransform();

	shadowTr.p += movement * SPEED;
	
}

void Copter::addMovement(Vector3 mov)
{
	movement += mov;
	float speed = movement.normalize();
	if (speed > 5) speed = 5;
	movement *= speed;
}

void Copter::resetMovement()
{
	movement = Vector3(0, 0, 0);
	extension = 0;
	magnet->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	magnet->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	magnet->clearForce();
}

void Copter::reset()
{
	movement = Vector3(0, 0, 0);
	extension = 0;
	magnetOffset = Vector3(0, 10, 0);
	PxTransform newPose{ ogPos };
	chain->setFPos(newPose.p - magnetOffset);
	top1->setGlobalPose(newPose);
	top2->setGlobalPose(newPose);
	newPose.p -= magnetOffset;
	magnet->setGlobalPose({ newPose });
	shadowTr.p = newPose.p;
	shadowTr.p.y = 1;
	magnet->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	magnet->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	cam->resetPos();
}

void Copter::extend(int value)
{
	extension = value;
}	

void Copter::cableTransform()
{
	const PxVec3& positionA = top1->getGlobalPose().p;
	const PxVec3& positionB = magnet->getGlobalPose().p;
	PxVec3 direction = positionB - positionA;
	int i = 1;
	for (auto& a : cableTr) {
		a.p = positionA + (direction / (NUM_CHAIN + 1)) * i;
		++i;
	}

}

void Copter::setTarget(PxRigidDynamic* target)
{
	magnetF->setTarget(target);
}

PxRigidDynamic* Copter::getMagnet()
{
	return magnet;
}

