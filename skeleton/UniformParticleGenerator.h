#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>
class UniformParticleGenerator : public ParticleGenerator
{

public: 
	UniformParticleGenerator(string name_, int num_particles_, double generation_probability_,
		Vector3 pos_widht, Vector3 vel_widht, Particle* base_p_);
	~UniformParticleGenerator();


	list<Particle*> generateParticles() override;
private:

	std::mt19937 gen;

	Vector3 pos_width;
	Vector3 vel_widht;

	uniform_real_distribution<> px;
	uniform_real_distribution<> py;
	uniform_real_distribution<> pz;

	uniform_real_distribution<> vx;
	uniform_real_distribution<> vy;
	uniform_real_distribution<> vz;

	std::uniform_real_distribution<double> distr;

	Vector3 _vel_widht, _pos_widht;
};

