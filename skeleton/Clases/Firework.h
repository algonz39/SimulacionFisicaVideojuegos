#pragma once
#include "Particle.h"
#include "ParticleSystem.h"

class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleSystem* Sys);
	~Firework();
	void onDeath();


private:
	ParticleSystem* sys;
};