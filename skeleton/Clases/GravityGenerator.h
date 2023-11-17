#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator 
{
public:
	GravityGenerator(Vector3 Pos,  float Mass);
	~GravityGenerator();
	void updateForce(Particle* particle) override;
private:
	const float G = 0.00000006673;
	Vector3 pos;
	float mass;
};