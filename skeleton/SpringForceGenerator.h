#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length,Particle* other);
	~SpringForceGenerator();
	
	virtual void updateForce(Particle* particle, double duration);

	void setK(double k) {
		_k = k;
	};


protected:
	double _k;
	double _resting_length;
	Particle* _other;
};

