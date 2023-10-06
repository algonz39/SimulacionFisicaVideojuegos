#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include <cmath>

ParticleSystem::ParticleSystem() {
	nParticles = 0;
	nGenerators = 0;
	cam = GetCamera();
}

ParticleSystem::~ParticleSystem() {
	for (Particle* p : particles) {
		if(p) delete p;
	}
	particles.clear();
}

void ParticleSystem::generateProjectile(ProjectileType type) {
	Vector3 pos = cam->getEye();
	Vector3 vel = cam->getDir();
	Vector3 grav = { 0, -1, 0 };
	Particle* projectile;
	switch (type)
	{
	case Pistol:
		projectile = new Particle(pos, vel * 20.0, grav, 2, {0.5, 0.5, 0.5, 1});
		break;
	case Artillery:
		projectile = new Particle(pos, vel * 20.0, grav * 20, 200, { 0.5, 0.5, 0.5, 1 }, 3);
		break;
	case FireBall:
		projectile = new Particle(pos, vel * 10.0, grav * -0.6, 1, { 1, 0, 0, 1 });
		break;
	case Laser:
		projectile = new Particle(pos, vel * 40.0, grav * 0, 0.1, { 1, 1, 0, 1 });
		break;
	default:
		break;
	}
	particles.push_back(projectile);
	nParticles++;

}

void ParticleSystem::updateParticles(double t)
{
	for (auto iter = particles.begin(); iter != particles.end();) {
		Particle* p = *iter;
		p->integrate(t);

		if (p->isDead()) {
			delete p;
			iter = particles.erase(iter);
		}
		else {
			++iter;  // Avanza el iterador si el objeto no está muerto
		}
	}
	for (ParticleGenerator* g : generators) {
		g->generate(t);
	}
}

Vector3 ParticleSystem::getGravity()
{
	return Vector3(0,-10,0);
}

void ParticleSystem::addParticle(Particle* p)
{
	particles.push_back(p);
	nParticles++;
}

void ParticleSystem::addGenerator(ParticleGenerator* g)
{
	generators.push_back(g);
	nGenerators++;

}

