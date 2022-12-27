#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>
class UniformParticleGenerator : public ParticleGenerator
{

public: 
	UniformParticleGenerator(string name_, int num_particles_, double generation_probability_,
		Vector3 pos_widht, Vector3 vel_widht, Vector3 mean_pos_, Vector3 mean_vel_, Particle* base_p_,typeForce T = GravityForce, double k1 = 0.3, double k2 = 0, double K = -10, Vector3 gravity = { 0,-9.8,0 }
	, Vector3 windVel = { 0,0,20 }, Vector3 whirlPos = { 0,50,0 }, bool active = true);


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

