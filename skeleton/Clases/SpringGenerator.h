#pragma once
#include "ForceGenerator.h"

class SpringGenerator : public ForceGenerator
{
public:
	SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Particle* p2);
	SpringGenerator(double lTime, double k, double restingLength, Particle* p1, Vector3 fixedPos);
	SpringGenerator(double lTime, double k, double restingLength, Particle* p1, PxRigidDynamic* rb);
	SpringGenerator(double lTime, double k, double restingLength, Vector3 fixedPos, PxRigidDynamic* rb);
	~SpringGenerator();

	void updateForce(Particle* particle) override;

	void updateForce(PxRigidDynamic* rigid) override;

	void setFPos(Vector3 fPos);

private:
	Particle *p1, *p2;
	Vector3 fixedPos;
	PxRigidDynamic* rb;
	double restingLength;
	double k;
};