#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, double Prob, double Velocity) 
	: pos(Pos), sys(Sys), genProb(Prob), velocity(Velocity) {
	sys->addGenerator(this);
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::generate(double t)
{
	if ((double)rand()/RAND_MAX < genProb) {
		Particle* p = new Particle(pos, getRandomVelocity() * velocity,sys->getGravity(),1);
		sys->addParticle(p);
	}
}

Vector3 ParticleGenerator::getRandomVelocity()
{
	return Vector3(
		static_cast<float>(std::rand()) / RAND_MAX * 2 - 1,
		static_cast<float>(std::rand()) / RAND_MAX * 2 - 1,
		static_cast<float>(std::rand()) / RAND_MAX * 2 - 1).getNormalized();
}
 