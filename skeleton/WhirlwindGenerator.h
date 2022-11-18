#pragma once
#include "WindGenerator.h"
class WhirlwindGenerator :public WindGenerator
{
public:

	WhirlwindGenerator() {};
	WhirlwindGenerator(const float k1, const float k2, float fuerza, Vector3 cT) :_k1(k1), _k2(k2), kF(fuerza), WhirlwindPos(cT) {};
	virtual void updateForce(Particle* p, double t);
	void setPos(Vector3 c);
	void  setForce(float nForce) { kF = nForce; }
	void addForce(float addedForce) { kF = addedForce; }

protected:
	float _k1;
	float _k2;
	float kF;
	Vector3 WhirlwindPos;
};