#pragma once
#include "Particle.h"
#include "Rigidbody.h"
#include <vector>
#include <unordered_set>

class ForceGenerator {
public:
	ForceGenerator(double lTime = 5);
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle) {}
	virtual void updateForce(PxRigidDynamic* body) {}
	bool updateLifeTime(double t);
	void kill();
	void addExcluded(Particle* p);
	void addExcluded(PxRigidDynamic* rb);

protected:
	double lifeTime;
	double time;
	std::unordered_set<Particle*> excluded;
	std::unordered_set<PxRigidDynamic*> excludedRb;
};