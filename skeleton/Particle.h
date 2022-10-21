#pragma once
#include "Firework.h"


enum TipoBala { PISTOL, ARTILLERY, FIREBALL, SNOWBALL };

struct particleVariables {
	Vector3 actionSpace;
	Vector3 actionSpaceWidth;
	Vector3 vel;
	Vector3 ace;
	Vector4 color;
	double damping, masa, lifeTime,tamano;
	bool isAlive_ = true, destroySpace;
	physx::PxTransform pose;
};

class Particle 
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp,double lifeTime_ , Vector4 color);
	Particle();
	virtual ~Particle();

	void integrate(double t);
	bool isAlive() { return p.isAlive_; };
	void setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace,
		Vector4 color, double tamano, Vector3 actionSpace_, Vector3 actionSpaceWidth_,bool dSpace_);

	Vector3 getMeanPos() { return p.pose.p; };
	Vector3 getMeanVel() { return p.vel; };

	Particle* clone() {
		Particle* pA = new Particle();
		pA->setParticle(p.masa, p.damping, p.lifeTime, p.vel, p.pose.p, p.ace, p.color, p.tamano, p.actionSpace, p.actionSpaceWidth, p.destroySpace);
		return pA;
	};
	
protected:


	RenderItem* renderItem;

private:

	particleVariables p;
};

