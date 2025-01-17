#include "WhirlwindGenerator.h"

WhirlwindGenerator::WhirlwindGenerator(double lTime, Vector3 Pos, Vector3 Area, float Vel, float k1, float k2) :
	DragGenerator(lTime, Pos, Area, Vector3( 0,0,0 ), k1, k2), velM(Vel)
{
}

void WhirlwindGenerator::updateForce(Particle* particle)
{
	if (excluded.count(particle)) return;
	Vector3 pPos = particle->getPos();
	if (pPos.y < (pos + area / 2).y && pPos.y >(pos - area / 2).y
		&& pPos.x < (pos + area / 2).x && pPos.x >(pos - area / 2).x
		&& pPos.z < (pos + area / 2).x && pPos.z >(pos - area / 2).z)
	{
		vel = pPos - pos;
		vel = Vector3(-vel.z, -vel.y, vel.x) * velM;
		Vector3 force = (vel - particle->getVel());
		force = k1 * force + k2 * force * force.magnitude();
		particle->addForce(force);
	}
}

void WhirlwindGenerator::updateForce(PxRigidDynamic* rb)
{
	if (excludedRb.count(rb)) return;
	Vector3 pPos = rb->getGlobalPose().p;
	if (pPos.y < (pos + area / 2).y && pPos.y >(pos - area / 2).y
		&& pPos.x < (pos + area / 2).x && pPos.x >(pos - area / 2).x
		&& pPos.z < (pos + area / 2).x && pPos.z >(pos - area / 2).z)
	{
		vel = pPos - pos;
		vel = Vector3(-vel.z, -vel.y, vel.x) * velM;
		Vector3 force = (vel - rb->getLinearVelocity());
		force = k1 * force + k2 * force * force.magnitude();
		rb->addForce(force);
	}
}
