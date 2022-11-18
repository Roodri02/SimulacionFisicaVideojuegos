#pragma once
#include "ParticleDragGenerator.h"
class WindGenerator :public ParticleDragGenerator
{
public:

	WindGenerator() {};
	WindGenerator(const float k1, const float k2, Vector3 windVel_) :_k1(k1), _k2(k2) , windVel(windVel_) {};
	
	void setk1k2(float k1k, float k2k) { _k1 = k1k; _k2 = k2k; }
	
	virtual void updateForce(Particle* p, double t);



protected:
	float _k1=0;
	float _k2=0;
	Vector3 windVel;

	double const cD = 0.5;
	double const pi = 3.1415926535;
	double const airDensity = 1.20;
};

