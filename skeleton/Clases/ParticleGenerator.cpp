#include "ParticleGenerator.h"
#include <cmath>

ParticleGenerator::ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, bool Gausian, ParticleData Data, double Prob, double Velocity, double Radius)
	: pos(Pos), sys(Sys), genProb(Prob), velocity(Velocity), data(Data), radius(Radius), gausian(Gausian) {
	sys->addGenerator(this);
}

ParticleGenerator::~ParticleGenerator()
{
	for (Particle* p : particles) {
		p->kill();
	}
}

void ParticleGenerator::generate(double t)
{
	if (sys->getRand()->generate(1) < genProb) {
		Particle* p = new Particle(pos + sys->getRand()->getRandomVector(gausian) * radius, sys->getRand()->getRandomVector(gausian) * velocity, sys->getGravity(), data);
		if (!sys->maxParticles()) {
			sys->addParticle(p);
			particles.push_back(p);
		}
		else delete p;
	}
} 