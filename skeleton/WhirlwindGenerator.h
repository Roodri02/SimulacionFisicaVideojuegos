#pragma once
#include "WindGenerator.h"
class WhirlwindGenerator :public WindGenerator
{
public:

	WhirlwindGenerator(double k1,double k2,double K_, Vector3 WhirlwindPos_) {
		_k1 = k1;
		_k2 = k2;
		K = K_;
		WhirlwindPos = WhirlwindPos_;
	};
	virtual void updateForce(Particle* p, double t);


protected:
	double K;
	Vector3 WhirlwindPos;
};