#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	Vector3 ace;
	double damping;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

