#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp);
	Particle();
	~Particle();

	void integrate(double t);
	
protected:

	void setMass(double mass_) { masa = mass_; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setPosition(Vector3 Pos) { pose.p = Pos; };
	void setAceleration(Vector3 Ace) { ace = Ace; };
	void setDamping(double damp) { damping = damp; };

private:


	Vector3 vel;
	Vector3 ace;
	double damping,masa;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

