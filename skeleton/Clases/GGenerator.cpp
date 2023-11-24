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
	
	particle->addForce(gravity * particle->getMass());
}
