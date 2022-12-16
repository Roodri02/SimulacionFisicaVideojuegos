#pragma once
#include "RigidForceGenerator.h"
#include "RigidParticle.h"
class RigidExplosionGenerator : public RigidForceGenerator
{

public:

	RigidExplosionGenerator(double K_, double radio_, double explosion_, Vector3 center_) {
		K = K_;
		center = center_;
		radio = radio_;
		explosion = explosion_;
	};

	virtual void updateForce(RigidParticle* p, double t);
	void addConst(double t) {
		explosion += t;
		radio = vE * t * 100;
	}
protected:
	double K, radio, explosion;
	double const e = 2.71828182845904525356;
	double vE = 343.55489;
	Vector3 center;
};

