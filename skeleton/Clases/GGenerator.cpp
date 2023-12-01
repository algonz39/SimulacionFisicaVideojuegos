#include "GGenerator.h"

GGenerator::GGenerator(double lTime, Vector3 Gravity)
	: ForceGenerator(lTime), gravity(Gravity)
{
}

GGenerator::~GGenerator()
{
}

void GGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	particle->addForce(gravity * particle->getMass());
}
