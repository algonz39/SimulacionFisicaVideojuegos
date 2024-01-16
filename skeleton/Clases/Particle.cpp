#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass, Vector4 color, float radius, float lifeTime, Shape shape, physx::PxQuat rotation, double Damp)
	: damp(Damp), vel(Vel) , acc (Acc), lifeTime(lifeTime), mass(mass), forces(Vector3(0,0,0))
{
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z, rotation);
	switch (shape) {
	case Sphere:
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pos, color);
		break;
	case Cube:
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(radius,radius,radius)), &pos, color);
		break;
	case Plane:
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(radius, 0.1, radius)), &pos, color);
		break;
	default:
		break;
	}
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleData Data, double Damp) :
	Particle(Pos, Vel, Acc, Data.mass, Data.color, Data.radius, Data.lifeTime, Data.shape, Data.rotation, Damp) {}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pos.p += vel * t;
	vel += (acc + forces / mass) * t;
	vel *= powf(damp, t);
	lifeTime -= t;
	clearForces();
}

void Particle::addForce(Vector3 force)
{
	forces += force;
}

void Particle::clearForces()
{
	forces = { 0,0,0 };
}

bool Particle::isDead()
{
	return lifeTime <= 0;
}

void Particle::kill()
{
	lifeTime = 0;
}

void Particle::setMass(float mass)
{
	if (mass <= 0) mass = 1;
	this->mass = mass;
}

