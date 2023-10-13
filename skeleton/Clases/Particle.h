#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"

struct ParticleData {
	float mass = 1;
	Vector4 color = { 0,1,0,1 };
	float radius = 1;
	float lifeTime = 3.0;
};

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass = 1, Vector4 color = {0,1,0,1}, float radius = 1, float lifeTime = 3.0, double Damp = 0.998);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleData Data, double Damp);
	~Particle();

	void integrate(double t);
	bool isDead();

private: 
	Vector3 vel;
	Vector3 acc;
	float mass;
	float lifeTime;
	physx::PxTransform pos;
	RenderItem* renderItem;
	const double damp;
};