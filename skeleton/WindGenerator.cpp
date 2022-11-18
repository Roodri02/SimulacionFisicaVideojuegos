#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* p, double t)
{


	if (fabs(1/p->getVariables().masa) < 1e-10)return;

	Vector3 v = p->getMeanVel() - windVel;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragF = -v * drag_coef;  //


	p->addForce(dragF);


};
void WindGenerator::setWindVel(Vector3 wV)
{
	windVel = wV;
}