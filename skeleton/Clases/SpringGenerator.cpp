#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Particle* p2)
	: ForceGenerator(lTime), k(k), restingLength(restingLength), p1(p1), p2(p2)
{
}

SpringGenerator::~SpringGenerator()
{
}

void SpringGenerator::updateForce(Particle* particle)
{
	Vector3 pos = { 0,0,0 };
	if (particle == p1) {
		pos = p2->getPos() - p1->getPos();
	}
	else if (particle == p2) {
		pos = p1->getPos() - p2->getPos();
	}
	float length = pos.magnitude();
	float delta = length - restingLength;
	particle->addForce(pos * delta * k);

}
