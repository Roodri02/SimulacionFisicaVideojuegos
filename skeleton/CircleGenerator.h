#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <memory>
#include <cmath>

class CircleGenerator : public ParticleGenerator
{

public:

	CircleGenerator(Vector3 mean_pos, double numParticles, double radio_,
		double generation_probability_, Particle* p , int tipo, typeForce type=GravityForce, double k1 = 0.5, double k2 = 0, double K = -20, Vector3 gravity = { 0,-9.8,0 }
	, Vector3 windVel = { 0,0,20 }, Vector3 whirlPos = { 0,50,0 });
	~CircleGenerator();

	list<Particle*> CircleGenerator::generateParticles() override;

private:
	double radio,angle=0;
	int tipo_;

	std::uniform_real_distribution<double> distr;
	normal_distribution<> tiempoVida;

	std::mt19937 gen;
};

