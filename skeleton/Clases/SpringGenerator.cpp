#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Particle* p2)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(p2), fixedPos(Vector3(0,0,0)), rb(nullptr)
{
}

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Vector3 fixedPos)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(nullptr), fixedPos(fixedPos), rb(nullptr)
{
}

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, PxRigidDynamic* rb)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(nullptr), fixedPos(Vector3(0, 0, 0)), rb(rb)
{
}

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Vector3 fixedPos, PxRigidDynamic* rb)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(nullptr), p2(nullptr), fixedPos(fixedPos), rb(rb)
{
}

SpringGenerator::~SpringGenerator()
{
}

void SpringGenerator::updateForce(Particle* particle)
{
	if (p1 == nullptr && rb == nullptr) lifeTime = 0;
	Vector3 pos = { 0,0,0 };
	if (particle == p1) {
		if (p2 != nullptr)
			pos = p2->getPos() - p1->getPos();
		else if (rb != nullptr)
			pos = rb->getGlobalPose().p - p1->getPos();
		else
			pos = fixedPos - p1->getPos();
	}
	else if (particle == p2) {
		pos = p1->getPos() - p2->getPos();
	}
	float length = pos.normalize();
	float delta = length - restingLength;
	particle->addForce(pos * delta * k);

}

void SpringGenerator::updateForce(PxRigidDynamic* rigid)
{
	if (rb == nullptr) return;
	Vector3 pos = { 0,0,0 };
	if (rigid == rb) {
		if (p2 != nullptr)
		pos = p1->getPos() - rb->getGlobalPose().p;
		else
		pos = fixedPos - rb->getGlobalPose().p;
	}
	float length = pos.normalize();
	rigid->addForce(pos * k * length);

}


void SpringGenerator::setFPos(Vector3 fPos)
{
	fixedPos = fPos;
}
