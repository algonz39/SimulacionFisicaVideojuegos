#include "Random.h"

float Random::generate(double t)
{
	return abs(uni(rd) * t);
}

Vector3 Random::getRandomVector(bool gausian)
{
	return gausian ? Vector3(norm(rd), norm(rd), norm(rd)).getNormalized() :
		Vector3(uni(rd), uni(rd), uni(rd)).getNormalized();
}
