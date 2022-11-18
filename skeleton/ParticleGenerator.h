#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"

using namespace std;

enum typeForce { GravityForce, WindForce, WhirlwindForce };

class ParticleGenerator 
{
public:
	ParticleGenerator() {};
	~ParticleGenerator() {};

	void setMeanPos(Vector3 mean_Pos, Vector3 mean_Vel) {
		mean_Pos_ = mean_Pos;
		if (mean_Vel_ == Vector3( 0, 0,0 ))mean_Vel_ = mean_Vel;
	};
	void setForceClon() {
		switch (typeForce_)
		{
		case GravityForce:
			fg = new GravityForceGenerator({ -5,-9.8,0 });
			break;
		case WindForce:
			fg = new WindGenerator(2, 0.3, { 0,0,5 });
			break;
		case WhirlwindForce:
			fg = new WhirlwindGenerator(-10, { 15,30,0 });
			break;
		default:
			break;
		}
	}


	ForceGenerator* getForceGenerator() {
		return fg;
	}

protected:

	ForceGenerator* fg;
	typeForce typeForce_;

	Vector3 mean_Pos_, mean_Vel_;
	Particle* model;

	string name;

	double generation_probability,mean_t;
	int num_particles;

public:

	virtual list<Particle*> generateParticles() = 0;
	

};

