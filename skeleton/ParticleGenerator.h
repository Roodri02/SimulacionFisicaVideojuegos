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

	void setMeanPos(Vector3 mean_Pos, Vector3 mean_Vel) {
		mean_Pos_ = mean_Pos;
		if (mean_Vel_ == Vector3( 0, 0,0 ))mean_Vel_ = mean_Vel;
	};

protected:


	Vector3 mean_Pos_, mean_Vel_;
	Particle* model;

	string name;

	double generation_probability,mean_t;
	int num_particles;

public:

	virtual list<Particle*> generateParticles() = 0;
	

};

