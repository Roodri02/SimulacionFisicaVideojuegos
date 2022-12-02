#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{

public:

	BuoyancyForceGenerator(float h, float a, float b, float c, float d);
	virtual void updateForce(Particle* p, double t);

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};