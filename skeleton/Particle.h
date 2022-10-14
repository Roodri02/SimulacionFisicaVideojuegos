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

	void setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace,
		Vector4 color, double tamano, Vector3 actionSpace_, Vector3 actionSpaceWidth_,bool dSpace_);
	
protected:


	RenderItem* renderItem;

private:

	Vector3 actionSpace;
	Vector3 actionSpaceWidth;
	Vector3 vel;
	Vector3 ace;
	double damping,masa,lifeTime;
	bool isAlive_=true,destroySpace;
	physx::PxTransform pose;
};

