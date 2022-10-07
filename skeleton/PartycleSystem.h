#pragma once
#include <list>
#include "Particle.h"
#include "GaussianParticleGenerator.h"

class PartycleSystem
{

public:
	PartycleSystem();
	~PartycleSystem();

	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particlesGenerators;
};

