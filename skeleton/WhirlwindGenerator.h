#pragma once
#include "WindGenerator.h"
class WhirlwindGenerator :public WindGenerator
{
public:

	WhirlwindGenerator(double K_, Vector3 WhirlwindPos_) {
		K = K_;
		WhirlwindPos = WhirlwindPos_;
	};
	virtual void updateForce(Particle* p, double t);


protected:
	double K;
	Vector3 WhirlwindPos;
};