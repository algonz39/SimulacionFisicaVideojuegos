#include "Random.h"

class PxMaterial;

float Random::generate(double t) {
	return abs(uni(rd) * t);
}

Vector3 Random::getRandomVector(bool gausian) {
	return gausian ? Vector3(norm(rd), norm(rd), norm(rd)).getNormalized() :
		Vector3(uni(rd), uni(rd), uni(rd)).getNormalized();
}

Vector4 Random::getRandomColor() {
	return { generate(1), generate(1), generate(1), 1 };
}

physx::PxShape* Random::getRandomShape(physx::PxMaterial* mat) {
	physx::PxShape* shape = nullptr;
	float rn = generate(1);
	if (rn < 0.5) {
		shape = CreateShape(physx::PxBoxGeometry(generate(3) + 2, generate(3) + 2, generate(3) + 2), mat);
	}
	else if (rn < 0.8) {
		shape = CreateShape(physx::PxCapsuleGeometry(generate(3) + 2, generate(3) + 2), mat);
	}
	else {
		shape = CreateShape(physx::PxSphereGeometry(generate(3) + 2), mat);
	}
	return shape;

}
