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

	string name;
	Vector3 mean_pos, mean_vel;

	Vector3 ambientPos;
	Vector3 ambientWidth;

	Vector4 color_;

	double generation_probability,mean_t;
	int num_particles;

	double  mass, damp , tamanio;
	bool destroySpace;
	Vector3 ace_;


public:

	virtual list<Particle*> generateParticles() = 0;
	

};

