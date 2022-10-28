#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <list>
#include <memory>

enum TipoBala { PISTOL, ARTILLERY, FIREBALL, SNOWBALL };

struct ParticleVariables {
	Vector3 actionSpace;
	Vector3 actionSpaceWidth;
	Vector3 vel;
	Vector3 ace;
	Vector4 color;
	double damping, masa, lifeTime,tamano;
	bool isAlive_ = true, destroySpace=false;
	physx::PxTransform pose;
	bool isVisible=true;
};


class Particle 
{
public:
	Particle(Vector3 pos, Vector3 Vel, Vector3 Ace,double damp,double lifeTime_ , Vector4 color);
	Particle();
	~Particle();

	virtual void integrate(double t);
	bool isAlive() { return p.isAlive_; };
	void setParticle(double mass_, double damp, double lifeTime_, Vector3 Vel, Vector3 Pos, Vector3 Ace, Vector4 color,
		double tamano, Vector3 actionSpace_, Vector3 actionSpaceWidth_, bool dSpace_, bool isVisible_);

	virtual void setParticle(Particle* p_);

	Vector3 getMeanPos() { return p.pose.p; };
	Vector3 getMeanVel() { return p.vel; };

	void setPosAndVel(Vector3 pos, Vector3 vel) {
		p.vel = vel;
		p.pose.p = pos;
		p.actionSpace = pos;
	}

	void setTime(double t) {
		p.lifeTime = t;
	}

	ParticleVariables getVariables() { return p; };

	Particle* clone() {
		Particle* pA = new Particle();
		pA->setParticle(this);
		return pA;
	};
	
protected:

	RenderItem* renderItem;
	ParticleVariables p;
};

