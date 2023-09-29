#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "Particle.h"
#include <vector>
class ParticleGenerator
{
public:
	enum ProjectileType {
		Pistol,
		Artillery,
		FireBall,
		Laser,
		LastEnum
	};
	ParticleGenerator();
	~ParticleGenerator();
	void generateProjectile(ProjectileType type);
	void updateParticles(double t);

private: 
	std::vector<Particle*> particles;

	int nParticles;
	Camera* cam;
};