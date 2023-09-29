#include "ParticleGenerator.h"
#include <cmath>

ParticleGenerator::ParticleGenerator()
{
	nParticles = 0;
	cam = GetCamera();
}

ParticleGenerator::~ParticleGenerator()
{
	for (Particle* p : particles) {
		delete p;
	}
	particles.clear();
}

void ParticleGenerator::generateProjectile(ProjectileType type)
{
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
		projectile = new Particle(pos, vel * 40.0, grav * 0, 0.1, { 0.5, 0.5, 0.5, 1 });
		break;
	}
	particles.push_back(projectile);
	nParticles++;

}

bool isDead(Particle* p) { return p->isDead(); }

void ParticleGenerator::updateParticles(double t)
{
	for (Particle* p : particles) {
		p->integrate(t);
	}
	
	std::remove_if(particles.begin(), particles.end(), isDead);
}

