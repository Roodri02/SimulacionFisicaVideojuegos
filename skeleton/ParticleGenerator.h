#pragma once
#include <list>
#include <string>
#include "Particle.h"
using namespace std;

class ParticleGenerator 
{
public:


protected:

	string name;
	Vector3 mean_pos, mean_vel;

	double generation_probability,mean_t;
	int num_particles;

	Particle* model;

public:

	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
	

};

