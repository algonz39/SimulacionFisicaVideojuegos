#include "../core.hpp"
#include "../RenderUtils.hpp"
class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float mass, Vector4 color = {0,1,0,1}, float radius = 1, float lifeTime = 3.0, double Damp = 0.998);
	~Particle();

	void integrate(double t);
	bool isDead();

private: 
	Vector3 vel;
	Vector3 acc;
	float mass;
	float lifeTime;
	physx::PxTransform pose;
	RenderItem* renderItem;
	const double damp;
};