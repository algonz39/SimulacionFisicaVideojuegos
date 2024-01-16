#include "MagnetGenerator.h"

MagnetGenerator::MagnetGenerator(PxRigidDynamic* magnet, float magnetForce, double lTime) : ForceGenerator(lTime), magnet(magnet), magnetForce(magnetForce)
{
	target = nullptr;
}

MagnetGenerator::~MagnetGenerator()
{
}

void MagnetGenerator::updateForce(PxRigidDynamic* rb)
{
	if (target == nullptr || rb != target) return;
	Vector3 force = (magnet->getGlobalPose().p - rb->getGlobalPose().p) * magnetForce / pow((magnet->getGlobalPose().p - rb->getGlobalPose().p).magnitude(), 2);
	
	rb->addForce(force);
	magnet->addForce(-force);
}

void MagnetGenerator::setTarget(PxRigidDynamic* trg)
{
	target = trg;
}