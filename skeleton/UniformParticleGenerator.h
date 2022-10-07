#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : ParticleGenerator
{

public: 
	UniformParticleGenerator();
	~UniformParticleGenerator();


	list<Particle*> generateParticles() override;

private:

	Vector3 _vel_widht, _pos_widht;
};

