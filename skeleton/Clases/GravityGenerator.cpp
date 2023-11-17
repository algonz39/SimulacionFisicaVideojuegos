#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(Vector3 Pos, float Mass) : pos(Pos), mass(Mass)
{
}

GravityGenerator::~GravityGenerator()
{
}

void GravityGenerator::updateForce(Particle* particle)
{
	Vector3 force = (pos - particle->getPos()) * mass * particle->getMass() * G / pow((pos - particle->getPos()).magnitude(),2);
	
	particle->addForce(force);
}
