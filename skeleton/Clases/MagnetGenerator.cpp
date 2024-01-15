#include "MagnetGenerator.h"

MagnetGenerator::MagnetGenerator(PxRigidDynamic* magnet, float magnetForce, double lTime) : ForceGenerator(lTime), magnet(magnet), magnetForce(magnetForce)
{
}

MagnetGenerator::~MagnetGenerator()
{
}

void MagnetGenerator::updateForce(PxRigidDynamic* rb)
{
	if (rb == magnet) return;
	Vector3 force = (magnet->getGlobalPose().p - rb->getGlobalPose().p) * magnetForce / pow((magnet->getGlobalPose().p - rb->getGlobalPose().p).magnitude(), 2);
	
	rb->addForce(force);
	magnet->addForce(-force);
}
