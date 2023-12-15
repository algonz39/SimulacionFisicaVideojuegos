#include "Rigidbody.h"

RigidBody::RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxShape* shape, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity, bool dynamic)
{
	rb = gPhysics->createRigidDynamic(PxTransform(Pos));
	rb->setLinearVelocity(linearVelocity);
	rb->setAngularVelocity(angularVelocity);
	rb->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*rb, density);
	new RenderItem(shape, rb, color);
}

RigidBody::RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal radius, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity, bool dynamic)
{
	PxShape* shape = CreateShape();
	RigidBody(gPhysics, gScene, Pos, shape, density, color, linearVelocity, angularVelocity, dynamic);
}

RigidBody::RigidBody(PxPhysics* gPhysics, PxScene* gScene, Vector3 Pos, PxReal x, PxReal y, PxReal z, PxReal density, Vector4 color, Vector3 linearVelocity, Vector3 angularVelocity, bool dynamic)
{
	PxShape* shape = CreateShape();
	RigidBody(gPhysics, gScene, Pos, shape, density, color, linearVelocity, angularVelocity, dynamic);
}
