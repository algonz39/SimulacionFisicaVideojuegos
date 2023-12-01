#pragma once
#include "ForceGenerator.h"

class SpringGenerator : public ForceGenerator
{
public:
	SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Particle* p2);
	SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Vector3 fixedPos);
	~SpringGenerator();
	void updateForce(Particle* particle) override;
private:
	Particle *p1, *p2;
	Vector3 fixedPos;
	double restingLength;
	double k;
};