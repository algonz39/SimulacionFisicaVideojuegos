#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass, Vector4 color, float radius, float lifeTime, double Damp) 
	: damp(Damp), vel(Vel) , acc (Acc), lifeTime(lifeTime)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pose, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
	vel += acc * t;
	vel *= powf(damp, t);
	lifeTime -= t;
}

bool Particle::isDead()
{
	return lifeTime <= 0;
}

