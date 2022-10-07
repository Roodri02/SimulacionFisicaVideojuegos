#pragma once
#include <list>
#include "Particle.h"

class PartycleSystem
{

public:
	PartycleSystem();
	~PartycleSystem();


protected:
	std::list<Particle*> _particles;
};

