#pragma once
#include "ForceGenerator.h"

class GGenerator : public ForceGenerator
{
public:
	GGenerator(double lTime, Vector3 Gravity);
	~GGenerator();
	void updateForce(Particle* particle) override;
private:
	Vector3 gravity;
};