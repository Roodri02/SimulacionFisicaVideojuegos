#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"


enum TipoBala { PISTOL, ARTILLERY, FIREBALL, SNOWBALL };


class Particle
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp,double lifeTime_ , Vector4 color);
	Particle();
	~Particle();

	void integrate(double t);
	bool isAlive() { return isAlive_; };
	
protected:

	void setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace,Vector4 color);
	RenderItem* renderItem;

private:


	Vector3 vel;
	Vector3 ace;
	double damping,masa,lifeTime;
	bool isAlive_=true;
	physx::PxTransform pose;
};

