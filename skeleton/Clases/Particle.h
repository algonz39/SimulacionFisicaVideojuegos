#pragma once
#include "../core.hpp"
#include "../RenderUtils.hpp"

enum Shape { Sphere, Cube, Plane };

struct ParticleData {
	float mass = 1;
	Vector4 color = { 0,1,0,1 };
	float radius = 1;
	float lifeTime = 3.0;
	Shape shape = Sphere;
};


const std::vector<Vector4> color = { {1,0,0,1},{0,1,0,1},{0,0,1,1} };

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass = 1, Vector4 color = {0,1,0,1}, float radius = 1, float lifeTime = 3.0, Shape shape = Sphere, double Damp = 0.998);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleData Data, double Damp = 0.998);
	virtual ~Particle();

	void integrate(double t);
	inline Vector3 getPos() { return pos.p; }
	inline Vector3 getVel() { return vel; }
	void addForce(Vector3 force);
	void clearForces();
	bool isDead();
	void kill();
	inline float getMass() { return mass; }
	void setMass(float mass);

protected: 
	Vector3 vel;
	Vector3 acc;
	Vector3 forces;
	float mass;
	float lifeTime;
	physx::PxTransform pos;
	RenderItem* renderItem;
	const double damp;
};