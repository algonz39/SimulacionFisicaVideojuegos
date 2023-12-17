#include "RigidBodyGenerator.h"
#include <cmath>
#include "Rigidbody.h"

RigidBodyGenerator::RigidBodyGenerator(Vector3 Pos, ParticleSystem* Sys, double Prob, double Velocity, double Radius)
	: pos(Pos), sys(Sys), genProb(Prob), velocity(Velocity), radius(Radius) {
	sys->addRBGenerator(this);
}

RigidBodyGenerator::~RigidBodyGenerator()
{
}

void RigidBodyGenerator::generate(double t)
{
	Random* rd = sys->getRand();
	if (rd->generate(1) < genProb && !sys->maxRB()) {
		PxRigidDynamic* rb;
		if (sys->getRand()->generate(1) < 0.5)
			rb = RigidBody::getDynamic(sys->getPhysics(), sys->getScene(), pos + sys->getRand()->getRandomVector(false) * radius,
				1 + rd->generate(9), 1000, rd->getRandomColor(), sys->getRand()->getRandomVector(false) * velocity);
		else
			rb = RigidBody::getDynamic(sys->getPhysics(), sys->getScene(), pos + sys->getRand()->getRandomVector(false) * radius,
				1 + rd->generate(9), 1 + rd->generate(9), 1 + rd->generate(9), 1000, rd->getRandomColor(), sys->getRand()->getRandomVector(false) * velocity);
		sys->addRigidBody(rb);
	}
} 