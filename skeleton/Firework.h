#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "ParticleGenerator.h"
#include <list>
#include <memory>

class Firework : public Particle
{

public:
	Firework();
	~Firework() {};

	int update(double t);

	std::list<Particle*> Explode();

private:

	std::list<std::shared_ptr<ParticleGenerator*>> gens; 

};

