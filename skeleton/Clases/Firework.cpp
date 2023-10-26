#include "Firework.h"
#include <vector>

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleSystem* Sys) : Particle(Pos,Vel,Acc, 1, { 0.5, 0.5, 0.5, 1 }, 1, 1.5), sys(Sys) {}

Firework::~Firework()
{
	onDeath();
}

void Firework::onDeath()
{
	std::vector<Vector4> color = { {1,0,0,1},{0,1,0,1},{0,0,1,1} };
	const int nParticles = 20 + rand() % 20;
	for (int i = 0; i < nParticles; ++i) {
		Particle* p = new Particle(pos.p, sys->getRand()->getRandomVector(false) * 15, sys->getGravity(), 1, color[rand() % 3]);
		if (!sys->maxParticles()) {
			sys->addParticle(p);
		}
		else {
			delete p;
			break;
		}

	}
}

