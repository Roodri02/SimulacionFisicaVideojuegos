#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* p, double t)
{


	if (fabs(1/p->getVariables().masa) < 1e-10)return;


	if (_k2 == 0) {
		_k2 = airDensity * cD * p->getVariables().tamano * 4 * pi;
	}

	Vector3 v = p->getMeanVel() - windVel;
	float drag_coef = v.normalize();
	
	Vector3 dragForce;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragForce = -v * drag_coef;  //


	p->addForce(dragForce);


};