#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"


enum TipoBala { PISTOL, ARTILLERY, FIREBALL, LASER };


class Particle
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp);
	Particle();
	~Particle();

	void integrate(double t);
	
protected:

	void setParticle(double mass_, double damp, Vector3 Vel, Vector3 Pos, Vector3 Ace);
	RenderItem* renderItem;

private:


	Vector3 vel;
	Vector3 ace;
	double damping,masa;
	physx::PxTransform pose;
};

