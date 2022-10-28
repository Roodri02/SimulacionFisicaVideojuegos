#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <memory>
#include <cmath>

class CircleGenerator : public ParticleGenerator
{

public:

	CircleGenerator(Vector3 mean_pos, double numParticles, double radio_,
		double generation_probability_, Particle* p , int tipo);
	~CircleGenerator();

	list<Particle*> CircleGenerator::generateParticles() override;

private:
	double radio,angle=0;
	int tipo_;

	std::uniform_real_distribution<double> distr;
	normal_distribution<> tiempoVida;

	std::mt19937 gen;
};

