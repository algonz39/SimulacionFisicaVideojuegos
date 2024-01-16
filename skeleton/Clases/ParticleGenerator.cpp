#include "ParticleGenerator.h"
#include <cmath>

ParticleGenerator::ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, bool Gausian, ParticleData Data, double Prob, double Velocity, double Radius, float duration)
	: pos(Pos), sys(Sys), genProb(Prob), velocity(Velocity), data(Data), radius(Radius), gausian(Gausian), type(Firework::LastType), duration(duration) {
	sys->addGenerator(this);
}

ParticleGenerator::ParticleGenerator(Vector3 Pos, ParticleSystem* Sys, Firework::FireType type, double Prob, double Velocity, double Radius, float duration)
	: pos(Pos), sys(Sys), genProb(Prob), velocity(Velocity), data(ParticleData()), radius(Radius), gausian(false), type(type), duration(duration) {
	sys->addGenerator(this);
}

ParticleGenerator::~ParticleGenerator()
{
	for (Particle* p : particles) {
		if(p != nullptr) p->kill();
	}
}

bool ParticleGenerator::generate(double t)
{
	if (sys->getRand()->generate(1) < genProb) {
		if (!sys->maxParticles()) {
		Particle* p;
		if (type == Firework::LastType)	{
			Vector3 vel = sys->getRand()->getRandomVector(gausian); vel.y = 1.0;
			p = new Particle(pos + sys->getRand()->getRandomVector(gausian) * radius, vel * velocity, { 0,0,0 }, data);
		}
		else
			p = new Firework(pos + sys->getRand()->getRandomVector(gausian) * radius, sys->getRand()->getRandomVector(gausian) * velocity, { 0,0,0 }, sys, type);

			sys->addParticle(p);
			particles.push_back(p);
		}
	}
	if (duration > 0) {
		duration -= t;
		if (duration <= 0) return true;
	}
	return false;
} 