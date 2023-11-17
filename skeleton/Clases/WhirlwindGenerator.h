#pragma once
#include "DragGenerator.h"

class WhirlwindGenerator : public DragGenerator
{
public:
	WhirlwindGenerator(double lTime, Vector3 Pos, Vector3 Area, float Vel, float k1, float k2 = 0);
	void updateForce(Particle* particle) override;
private:
	float velM;
};