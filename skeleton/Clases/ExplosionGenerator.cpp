#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(double lTime, Vector3 Pos, float velocity, float K, float t) : ForceGenerator(lTime), pos(Pos), velocity(velocity), K(K), t(t)
{
}

void ExplosionGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	if ((particle->getPos() - pos).magnitude() >= time * velocity) {
		Vector3 force = (particle->getPos() - pos) * K / pow((particle->getPos() - pos).magnitude(), 2) * exp(-time / t);

		particle->addForce(force);
	}
}

void ExplosionGenerator::updateForce(PxRigidDynamic* rb)
{
	if (excludedRb.count(rb)) return;
	if ((rb->getGlobalPose().p - pos).magnitude() >= time * velocity) {
		Vector3 force = (rb->getGlobalPose().p - pos) * K / pow((rb->getGlobalPose().p - pos).magnitude(), 2) * exp(-time / t);

		rb->addForce(force);
	}
}


