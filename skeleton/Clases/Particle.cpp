#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass, Vector4 color, float radius, float lifeTime, double Damp) 
	: damp(Damp), vel(Vel) , acc (Acc), lifeTime(lifeTime)
{
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pos, color);
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleData Data, double Damp) :
	Particle(Pos, Vel, Acc, Data.mass, Data.color, Data.radius, Data.lifeTime, Damp) {}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pos.p += vel * t;
	vel += acc * t;
	vel *= powf(damp, t);
	lifeTime -= t;
}

bool Particle::isDead()
{
	return lifeTime <= 0;
}

