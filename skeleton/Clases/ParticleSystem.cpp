#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "Firework.h"
#include <cmath>

ParticleSystem::ParticleSystem() {
	nParticles = 0;
	nGenerators = 0;
	cam = GetCamera();
	rand = new Random();
}

ParticleSystem::~ParticleSystem() {
	for (Particle* p : particles) {
		if(p) delete p;
	}
	particles.clear();
	nParticles = 0;
	delete rand;
}

void ParticleSystem::generateProjectile(ProjectileType type) {
	if (maxParticles()) return;
	Vector3 pos = cam->getEye();
	Vector3 vel = cam->getDir();
	Vector3 grav = {0,0,0};
	Particle* projectile;
	switch (type)
	{
	case Pistol:
		projectile = new Particle(pos, vel * 20.0, grav / 10, 2, {0.5, 0.5, 0.5, 1});
		break;
	case Artillery:
		projectile = new Particle(pos, vel * 20.0, grav * 2, 200, { 0.5, 0.5, 0.5, 1 }, 3);
		break;
	case FireBall:
		projectile = new Particle(pos, vel * 10.0, grav * -0.06, 1, { 1, 0, 0, 1 });
		break;
	case Laser:
		projectile = new Particle(pos, vel * 40.0, grav * 0, 0.1, { 1, 1, 0, 1 });
		break;
	case FireworkR:
		projectile = new Firework(pos, vel * 35.0, grav * 0.05, this, Firework::Fireworks);
		break;
	case FireworkC:
		projectile = new Firework(pos, vel * 35.0, grav * 0.05, this, Firework::Circles);
		break;
	case FireworkS:
		projectile = new Firework(pos, vel * 35.0, grav * 0.05, this, Firework::Swirl);
		break;
	default:
		break;
	}
	addParticle(projectile);
}

void ParticleSystem::update(double t)
{
	for (auto iter = forces.begin(); iter != forces.end();) {
		ForceGenerator* f = *iter;
		if (f->updateLifeTime(t)) {
			delete f; f = nullptr;
			iter = forces.erase(iter);
			nForces--;
		}
		else {
			for (Particle* p : particles) {
				f->updateForce(p);
			}
			iter++;
		}
	}
	for (auto iter = particles.begin(); iter != particles.end();) {
		Particle* p = *iter;
		p->integrate(t);

		if (p->isDead()) {
			delete p; p = nullptr;
			iter = particles.erase(iter);
			nParticles--;
		}
		else {
			++iter;  // Avanza el iterador si el objeto no está muerto
		}
	}
	for (ParticleGenerator* g : generators) {
		g->generate(t);
	}
	for (Particle* p : particlesToAdd) {
		particles.push_back(p);
		nParticles++;
	}
	particlesToAdd.clear();
}

Particle* ParticleSystem::addParticle(Particle* p)
{
	particlesToAdd.push_back(p);
	return p;
}

ParticleGenerator* ParticleSystem::addGenerator(ParticleGenerator* g)
{
	generators.push_back(g);
	nGenerators++;
	return g;

}

ForceGenerator* ParticleSystem::addForce(ForceGenerator* f)
{
	forces.push_back(f);
	nForces++;
	return f;
}

bool ParticleSystem::maxParticles()
{
	return nParticles >= MAX_PARTICLES;
}

Random* ParticleSystem::getRand() {
	return rand;
}

