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
	if ((double)rand()/RAND_MAX < genProb) {
		Particle* p = new Particle(pos + getRandomVector() * radius, getRandomVector() * velocity, sys->getGravity(), data);
		if (sys->addParticle(p))
			particles.push_back(p);
		else delete p;
	}
}

Vector3 ParticleGenerator::getRandomVector()
{
	return gausian ? Vector3(norm(rd), norm(rd), norm(rd)).getNormalized() :
		Vector3(uni(rd), uni(rd), uni(rd)).getNormalized();
}
 