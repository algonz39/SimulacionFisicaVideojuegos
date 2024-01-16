#pragma once
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include <map>
using namespace physx;

static class RigidBody
{
	std::map<PxRigidStatic*, RenderItem*> staticRender;

public:
	static std::pair<PxRigidDynamic*, RenderItem*> getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, PxReal density, Vector4 color, Vector3 linearVelocity = Vector3(0, 0, 0), Vector3 angularVelocity = Vector3(0, 0, 0));
	static std::pair<PxRigidDynamic*, RenderItem*> getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal radius, PxReal density, Vector4 color, Vector3 linearVelocity = Vector3(0, 0, 0), Vector3 angularVelocity = Vector3(0, 0, 0));
	static std::pair<PxRigidDynamic*, RenderItem*> getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal x, PxReal y, PxReal z, PxReal density, Vector4 color, Vector3 linearVelocity = Vector3(0,0,0), Vector3 angularVelocity = Vector3(0, 0, 0));
	static PxRigidStatic* getStatic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, Vector4 color, PxQuat rot = PxQuat(1));
	static std::pair<PxRigidStatic*, RenderItem*> getStaticandRender(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, Vector4 color, PxQuat rot);
};