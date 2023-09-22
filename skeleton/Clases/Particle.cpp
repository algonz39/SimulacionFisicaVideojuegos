#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	vel = Vel;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, {0,1,0,1});
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
}
