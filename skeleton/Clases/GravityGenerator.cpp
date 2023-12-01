#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(Vector3 Pos, float Mass, double lTime) 
	: ForceGenerator(lTime), pos(Pos), mass(Mass)
{
}

GravityGenerator::~GravityGenerator()
{
}

void GravityGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	Vector3 force = (pos - particle->getPos()) * mass * particle->getMass() * G / pow((pos - particle->getPos()).magnitude(),2);
	
	particle->addForce(force);
}
