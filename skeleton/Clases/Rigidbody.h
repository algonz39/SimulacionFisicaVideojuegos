#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"

using namespace physx;

class RigidBody
{
public:
	RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, PxReal density, Vector4 color, Vector3 linearVelocity = Vector3(), Vector3 angularVelocity = Vector3(), bool dynamic = true);
	RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal radius, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity, bool dynamic = true);
	RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal x, PxReal y, PxReal z, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity, bool dynamic = true);
	inline PxRigidBody* getBody() { return rb; }
private:
	PxRigidBody* rb;
};