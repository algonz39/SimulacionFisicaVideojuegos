#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Particle* p2)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(p2), fixedPos(Vector3(0,0,0))
{
}

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Vector3 fixedPos)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(nullptr), fixedPos(fixedPos)
{
}

SpringGenerator::~SpringGenerator()
{
}

void SpringGenerator::updateForce(Particle* particle)
{
	if (p1 == nullptr) lifeTime = 0;
	Vector3 pos = { 0,0,0 };
	if (particle == p1) {
		if (p2 != nullptr)
			pos = p2->getPos() - p1->getPos();
		else
			pos = fixedPos - p1->getPos();
	}
	else if (particle == p2) {
		pos = p1->getPos() - p2->getPos();
	}
	float length = pos.magnitude();
	float delta = length - restingLength;
	particle->addForce(pos * delta * k);

}
