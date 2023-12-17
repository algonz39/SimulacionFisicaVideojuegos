#pragma once
#include "../core.hpp"
#include <random>

class Random
{
public:
	Random() {}
	~Random() {}
	float generate(double t);
	Vector3 getRandomVector(bool gausian);
	Vector4 getRandomColor();


private: 

	std::random_device rd{};
	std::mt19937 gen{rd()};
	
	std::uniform_real_distribution<float> uni{-1.0,1.0};
	std::normal_distribution<float> norm{ 0.0, 1.0 };
};