#include "BouyancyForceGenerator.h"

BouyancyForceGenerator::BouyancyForceGenerator(double lTime, Vector3 pos, float height, float volume, float density)
	:ForceGenerator(lTime), height(height), volume(volume), density(density)
{
	liquidParticle = new Particle(pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 1, { 0,0,1,1 }, 30, 1000, Plane, PxQuat(PxPi / 4, { 0,1,0 }));
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

void BouyancyForceGenerator::updateForce(PxRigidDynamic* rb)
{
	float h = rb->getGlobalPose().p.y;
	float h0 = liquidParticle->getPos().y;

	Vector3 force (0, 0, 0);
	float inmersion = 0;
	if (h - h0 > height * 0.5) inmersion = 0;
	if (h0 - h > height * 0.5) inmersion = 1;
	else inmersion = (h0 - h) / height + 0.5;
	force.y = density * volume * inmersion * gravity;

	rb->addForce(force);
}
