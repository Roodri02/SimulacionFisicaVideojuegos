#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>


class GaussianParticleGenerator : public ParticleGenerator
{
public:
	GaussianParticleGenerator(string name,Vector3 std_dev_pos_, Vector3 std_dev_vel_, double std_dev_t_,double _mean_t_, int num_particles_ ,
		double generation_probability_,Particle* p,typeForce T = GravityForce);
	GaussianParticleGenerator(string name, Vector3 std_dev_pos_, Vector3 std_dev_vel_, Vector3 mean_pos_, Vector3 mean_vel_, double std_dev_t_, double _mean_t_, int num_particles_,
		double generation_probability_, Particle* p, typeForce T = GravityForce);

	~GaussianParticleGenerator();

	list<Particle*> generateParticles() override;


private:

	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

	std::mt19937 gen;

	normal_distribution<> px;
	normal_distribution<> py;
	normal_distribution<> pz;

	normal_distribution<> vx;
	normal_distribution<> vy;
	normal_distribution<> vz;

	std::uniform_real_distribution<double> distr;
	normal_distribution<> tiempoVida;


};

