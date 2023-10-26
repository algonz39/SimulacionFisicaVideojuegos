#pragma once
#include "Particle.h"
#include "ParticleSystem.h"

class Firework : public Particle
{
public:
	enum FireType {Random,Circles,Swirl,Fireworks};
	Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, ParticleSystem* Sys, FireType Fire);
	~Firework();
	void onDeath();


private:
	ParticleSystem* sys;
	FireType fire;
};