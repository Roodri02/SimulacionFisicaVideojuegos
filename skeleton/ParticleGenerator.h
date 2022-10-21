#pragma once
#include <list>
#include <string>
#include "Particle.h"
using namespace std;

class ParticleGenerator 
{
public:
	ParticleGenerator() {};
	~ParticleGenerator() {};

protected:

	Particle* model;

	string name;

	double generation_probability,mean_t;
	int num_particles;

public:

	virtual list<Particle*> generateParticles() = 0;
	

};

