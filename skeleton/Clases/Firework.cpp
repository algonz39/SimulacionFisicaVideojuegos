#include "Firework.h"
#include <vector>

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleSystem* Sys, FireType Fire) :
	Particle(Pos, Vel, Acc, 1, { 0.5, 0.5, 0.5, 1 }, 1, 1.5), sys(Sys), fire(Fire) {}

Firework::~Firework()
{
	onDeath();
}

void Firework::onDeath()
{
	const int nParticles = 30 + sys->getRand()->generate(20);
	switch (fire) {
	case Random:
		for (int i = 0; i < nParticles; ++i) {
			Particle* p = new Particle(pos.p, sys->getRand()->getRandomVector(true) * 15, { 0,0,0 }, 1, color[sys->getRand()->generate(3)]);
			if (!sys->maxParticles()) {
				sys->addParticle(p);
			}
			else {
				delete p;
				break;
			}
		}
		break;
	case Fireworks:
		for (int i = 0; i < nParticles / 7; ++i) {
			Particle* p = new Firework(pos.p, sys->getRand()->getRandomVector(false) * 10, { 0,0,0 }, sys, Random);
			if (!sys->maxParticles()) {
				sys->addParticle(p);
			}
			else {
				delete p;
				break;
			}
		}
		break;
	case Swirl:
		for (int i = 0; i < nParticles; ++i) {
			Vector3 mov = Vector3(cos(2 * nParticles + i * 360 / 4), 0, sin(2 * nParticles + i * 360 / 4));
			Particle* p = new Particle(pos.p, mov * (50 - i), { 0,0,0 }, 1, color[sys->getRand()->generate(3)]);
			if (!sys->maxParticles()) {
				sys->addParticle(p);
			}
			else {
				delete p;
				break;
			}
		}
		break;
	case Circles:
		int nCircles = 2 + sys->getRand()->generate(5);
		for (int j = 1; j < nCircles; ++j) {
			for (int i = 0; i < nParticles; ++i) {
				Vector3 mov = Vector3(sin(i * 360 / nParticles), 0, cos(i * 360 / nParticles));
				Particle* p = new Particle(pos.p, mov * 5 * j, { 0,0,0 }, 1, color[sys->getRand()->generate(3)]);
				if (!sys->maxParticles()) {
					sys->addParticle(p);
				}
				else {
					delete p;
					break;
				}
			}
		}
		break;
	}

}
