#pragma once
#include "ForceGenerator.h"

class BouyancyForceGenerator : public ForceGenerator
{
public:
	BouyancyForceGenerator(double lTime, Vector3 pos, float height, float volume, float density);
	~BouyancyForceGenerator();
	void updateForce(Particle* particle) override;
	void updateForce(PxRigidDynamic* rb) override;
protected:
	float height;
	float volume;
	float density;
	const float gravity = 9.8;
	Particle* liquidParticle;
};