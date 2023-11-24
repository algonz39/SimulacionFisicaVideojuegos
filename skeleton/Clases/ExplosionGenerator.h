#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator 
{
public:
	ExplosionGenerator(double lTime, Vector3 Pos, float velocity, float K, float t);
	void updateForce(Particle* particle) override;
protected:
	Vector3 pos;
	float velocity;
	float K;
	float t;
};