#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>


class GaussianParticleGenerator : ParticleGenerator
{
public:
	GaussianParticleGenerator(Vector3 std_dev_pos_, Vector3 std_dev_vel_, double std_dev_t_,double _mean_t_, int num_particles_ , double generation_probability_,Vector3 mean_pos_,Vector3 mean_vel_);
	~GaussianParticleGenerator();

	list<Particle*> generateParticles() override;

private:

	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
	std::mt19937 gen;

	normal_distribution<> px{ mean_pos.x, std_dev_pos.x };
	normal_distribution<> py{ mean_pos.y, std_dev_pos.y };
	normal_distribution<> pz{ mean_pos.z, std_dev_pos.z };

	normal_distribution<> vx{ mean_vel.x, std_dev_vel.x };
	normal_distribution<> vy{ mean_vel.y, std_dev_vel.y };
	normal_distribution<> vz{ mean_vel.z, std_dev_vel.z };

	std::uniform_real_distribution<double> distr;

};

