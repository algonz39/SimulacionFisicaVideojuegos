#pragma once
#include "ForceGenerator.h"

class DragGenerator : public ForceGenerator 
{
public:
	DragGenerator(double lTime, Vector3 Pos, Vector3 Area, Vector3 Vel, float k1, float k2 = 0);
	~DragGenerator();
	void updateForce(Particle* particle) override;
protected:
	float k1;
	float k2;
	Vector3 pos;
	Vector3 area;
	Vector3 vel;
};