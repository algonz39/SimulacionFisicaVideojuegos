#include "Copter.h"
#include "SpringGenerator.h"

Copter::Copter(PxPhysics* gPhysics, PxScene* gScene, ParticleSystem* pSystem, Vector3 pos) : gPhysics(gPhysics), gScene(gScene), pSystem(pSystem), magnetOffset(Vector3(0, 10, 0))
{
	cam = GetCamera();

	top1 = RigidBody::getStatic(gPhysics, gScene, { pos }, CreateShape(physx::PxBoxGeometry(6, 1, 2)), { 1,0,0,1 });
	top2 = RigidBody::getStatic(gPhysics, gScene, { pos }, CreateShape(physx::PxBoxGeometry(2, 1, 6)), { 1,0,0,1 });
	pSystem->addRigidBody(magnet = RigidBody::getDynamic(gPhysics, gScene, pos - magnetOffset, 1, 0.5, 1, 15, { 0.1,0.1,0.1,1 }));

	pSystem->addForce(chain = new SpringGenerator(-1, 50, 10, pos - magnetOffset, magnet));
	pSystem->addForce(magnetF = new MagnetGenerator(magnet, 300, -1 ));

	pSystem->addRigidBody(RigidBody::getDynamic(gPhysics, gScene, pos - 3*magnetOffset, 1, 1, 1, 0.5, { 0.1,0.1,0.1,1 }));


}

Copter::~Copter()
{

}

void Copter::move(Vector3 movement)
{
	PxTransform newPose{ top1->getGlobalPose().p += movement };
	chain->setFPos(newPose.p - magnetOffset);
	cam->setEye(movement);
	top1->setGlobalPose(newPose);
	top2->setGlobalPose(newPose);
}

void Copter::extend(int value)
{
	magnetOffset.y += value * 0.5;
	if (magnetOffset.y < 10) magnetOffset.y = 10;
	else if(magnetOffset.y > 30) magnetOffset.y = 30;
	chain->setFPos(top1->getGlobalPose().p - magnetOffset);

}
