#include "../core.hpp"
#include "../RenderUtils.hpp"
class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();

	void integrate(double t);

private: 
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};