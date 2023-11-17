#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator 
{
public:
	ExplosionGenerator(double lTime, Vector3 Pos);
	~ExplosionGenerator();
	void updateForce(Particle* particle) override;
protected:
	Vector3 pos;
	Vector3 area;
};