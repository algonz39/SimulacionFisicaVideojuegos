#include "DragGenerator.h"

DragGenerator::DragGenerator(double lTime, Vector3 Pos, Vector3 Area, Vector3 Vel, float K1, float K2)
	: ForceGenerator(lTime), pos(Pos), area(Area), vel(Vel), k1(K1), k2(K2)
{
}

DragGenerator::~DragGenerator()
{
}

void DragGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	Vector3 pPos = particle->getPos();
	if (pPos.y < (pos + area / 2).y && pPos.y >(pos - area / 2).y
		&& pPos.x < (pos + area / 2).x && pPos.x >(pos - area / 2).x)
	{
		Vector3 force = (vel - particle->getVel());
		force = k1 * force + k2 * force * force.magnitude();
		particle->addForce(force);
	}
}
