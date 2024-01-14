#pragma once
#include "ForceGenerator.h"

class MagnetGenerator : public ForceGenerator 
{
public:
	MagnetGenerator(PxRigidDynamic* magnet,  float magnetForce, double lTime);
	~MagnetGenerator();
	void updateForce(PxRigidDynamic* body) override;
private:
	PxRigidDynamic* magnet;
	float magnetForce;
};