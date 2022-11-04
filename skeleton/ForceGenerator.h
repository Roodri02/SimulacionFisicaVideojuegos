#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	std::string name;
	double t = -1e10;
};

