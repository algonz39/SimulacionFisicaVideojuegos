#include "Rigidbody.h"

PxRigidDynamic* RigidBody::getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity)
{
	PxRigidDynamic* rb = gPhysics->createRigidDynamic(PxTransform(Pos));
	rb->setLinearVelocity(linearVelocity);
	rb->setAngularVelocity(angularVelocity);
	PxRigidBodyExt::updateMassAndInertia(*rb, density);
	rb->attachShape(*shape);
	new RenderItem(shape, rb, color);
	gScene->addActor(*rb);
	return rb;
}

PxRigidDynamic* RigidBody::getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal radius, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity)
{
	PxShape* shape = CreateShape(physx::PxSphereGeometry(radius));
	return getDynamic(gPhysics, gScene, Pos, shape, density, color, linearVelocity, angularVelocity);
}

PxRigidDynamic* RigidBody::getDynamic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal x, PxReal y, PxReal z, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity)
{
	PxShape* shape = CreateShape(physx::PxBoxGeometry(x, y, z));
	return getDynamic(gPhysics, gScene, Pos, shape, density, color, linearVelocity, angularVelocity);
}


PxRigidStatic* RigidBody::getStatic(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, Vector4 color)
{
	PxRigidStatic* rs = gPhysics->createRigidStatic(PxTransform(Pos));
	rs->attachShape(*shape);
	new RenderItem(shape, rs, color);
	gScene->addActor(*rs);
	return rs;
}
