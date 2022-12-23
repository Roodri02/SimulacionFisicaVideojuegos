#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"

using namespace std;

enum typeForce { GravityForce, WindForce, WhirlwindForce,Nada };

class ParticleGenerator 
{
public:
	ParticleGenerator() {};
	~ParticleGenerator() {};

	void setMeanPos(Vector3 mean_Pos, Vector3 mean_Vel) {
		mean_Pos_ = mean_Pos;
		if (mean_Vel_ == Vector3( 0, 0,0 ))mean_Vel_ = mean_Vel;
	};

	void setForceGenerator(Vector3 gravity,double k1, double k2, Vector3 windVel, double K, Vector3 WhirlPos  ) {
		switch (typeForce_)
		{
		case GravityForce:
			fg = new GravityForceGenerator(gravity);
			break;
		case WindForce:
			fg = new WindGenerator(k1,k2, windVel);
			break;
		case WhirlwindForce:
			fg = new WhirlwindGenerator(k1,k2,K, WhirlPos);
			break;
		default:
			break;
		}
	}


	ForceGenerator* getForceGenerator() {
		return fg;
	}

protected:

	ForceGenerator* fg=nullptr;
	typeForce typeForce_;

	Vector3 mean_Pos_, mean_Vel_;
	Particle* model;

	string name;

	double generation_probability,mean_t;
	int num_particles;

public:

	virtual list<Particle*> generateParticles() = 0;
	

};

