#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(double lTime, Vector3 Pos, float velocity, float K, float t) : ForceGenerator(lTime), pos(Pos), velocity(velocity), K(K), t(t)
{
}

void ExplosionGenerator::updateForce(Particle* particle)
{
	if ((particle->getPos() - pos).magnitude() >= time * velocity) {
		Vector3 force = (particle->getPos() - pos) * K / pow((particle->getPos() - pos).magnitude(), 2) * exp(-time / t);

		particle->addForce(force);
	}
}


