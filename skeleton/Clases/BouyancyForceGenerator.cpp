#include "BouyancyForceGenerator.h"

BouyancyForceGenerator::BouyancyForceGenerator(double lTime, Particle* liquidParticle, float height, float volume, float density)
	:ForceGenerator(lTime), liquidParticle(liquidParticle), height(height), volume(volume), density(density)
{
}

BouyancyForceGenerator::~BouyancyForceGenerator()
{
}

void BouyancyForceGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	if (particle != liquidParticle) {
		float h = particle->getPos().y;
		float h0 = liquidParticle->getPos().y;

		Vector3 force (0, 0, 0);
		float inmersion = 0;
		if (h - h0 > height * 0.5) inmersion = 0;
		if (h0 - h > height * 0.5) inmersion = 1;
		else inmersion = (h0 - h) / height + 0.5;
		force.y = density * volume * inmersion * gravity;

		particle->addForce(force);
	}
}
