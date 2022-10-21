#pragma once
#include <list>
#include "Firework.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"

class PartycleSystem
{

public:
	PartycleSystem();
	~PartycleSystem();

	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void shootFirework(int type);
	void OnParticleDeath(Particle* p);
	void generateFireworkSystem();

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particlesGenerators;

	std::vector<Firework*> fireworks_pool;
	ParticleGenerator* firework_gen;
};

