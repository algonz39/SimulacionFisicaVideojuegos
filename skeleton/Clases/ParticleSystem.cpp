#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "RigidBodyGenerator.h"
#include "ForceGenerator.h"
#include "Firework.h"
#include <cmath>


ParticleSystem::ParticleSystem(PxPhysics* gPhysics, PxScene* gScene) : gPhysics(gPhysics), gScene(gScene) {
	nParticles = 0;
	nGenerators = 0;
	nForces = 0;
	nRigidBodys = 0;
	cam = GetCamera();
	rand = new Random();
}


ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* g : generators) {
		if (g) delete g;
	}
	generators.clear();
	nGenerators = 0;
	for (Particle* p : particles) {
		if (p) delete p;
	}
	particles.clear();
	nParticles = 0;
	for (ForceGenerator* f : forces) {
		if(f) delete f;
	}
	forces.clear();
	nForces = 0;	
	rigidBodys.clear();	
	nRigidBodys = 0;
	delete rand;
}

void ParticleSystem::update(double t)
{
	for (auto iter = forces.begin(); iter != forces.end();) {
		ForceGenerator* f = *iter;
		if (f->updateLifeTime(t)) {
			delete f; f = nullptr;
			iter = forces.erase(iter);
			nForces--;
		}
		else {
			for (Particle* p : particles) {
				f->updateForce(p);
			}
			for (PxRigidDynamic* rb : rigidBodys) {
				if(rb != nullptr) f->updateForce(rb);
			}
			iter++;
		}
	}
	for (auto iter = particles.begin(); iter != particles.end();) {
		Particle* p = *iter;
		p->integrate(t);

		if (p->isDead()) {
			delete p; p = nullptr;
			iter = particles.erase(iter);
			nParticles--;
		}
		else {
			++iter;  // Avanza el iterador si el objeto no está muerto
		}
	}
	for (auto iter = generators.begin(); iter != generators.end();) {
		ParticleGenerator* g = *iter;
		if (g->generate(t))	{
			delete g; g = nullptr;
			iter = generators.erase(iter);
			nGenerators--;
		}
		else {
			++iter;
		}
	}
	for (RigidBodyGenerator* g : rbGenerators) {
		g->generate(t);
	}
	for (Particle* p : particlesToAdd) {
		particles.push_back(p);
		nParticles++;
	}
	particlesToAdd.clear();
}

Particle* ParticleSystem::addParticle(Particle* p)
{
	particlesToAdd.push_back(p);
	return p;
}

ParticleGenerator* ParticleSystem::addGenerator(ParticleGenerator* g)
{
	generators.push_back(g);
	nGenerators++;
	return g;

}

RigidBodyGenerator* ParticleSystem::addRBGenerator(RigidBodyGenerator* g)
{
	rbGenerators.push_back(g);
	nGenerators++;
	return g;
}

ForceGenerator* ParticleSystem::addForce(ForceGenerator* f)	
{
	forces.push_back(f);
	nForces++;
	return f;
}

PxRigidDynamic* ParticleSystem::addRigidBody(std::pair<PxRigidDynamic*, RenderItem*> rb)
{
	rigidBodys.push_back(rb.first);
	nRigidBodys++;
	renderItems.insert(rb);
	return rb.first;
}

void ParticleSystem::releaseRb(PxRigidDynamic* rb)
{
	for (auto iter = rigidBodys.begin(); iter != rigidBodys.end();) {
		if (*iter == rb) {
			iter = rigidBodys.erase(iter);
			nRigidBodys--;
			DeregisterRenderItem(renderItems[rb]);
			renderItems.erase(rb);
			rb->release();
		}
		else {
			++iter;
		}
	}

}

bool ParticleSystem::maxParticles()
{
	return nParticles >= MAX_PARTICLES;
}

bool ParticleSystem::maxRB()
{
	return nRigidBodys >= MAX_RB;
}

Random* ParticleSystem::getRand() {
	return rand;
}

PxPhysics* ParticleSystem::getPhysics()
{
	return gPhysics;
}

PxScene* ParticleSystem::getScene()
{
	return gScene;
}

