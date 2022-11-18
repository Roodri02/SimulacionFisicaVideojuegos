#include "WhirlwindGenerator.h"

void WhirlwindGenerator::updateForce(Particle* p, double t)
{

	if (fabs(1/p->getVariables().masa) < 1e-10) {
		return;
	}

	Vector3 force;
	Vector3 particlePos = p->getMeanPos();

	Vector3 v(-(particlePos.z - WhirlwindPos.z), 50 - (particlePos.y - WhirlwindPos.y), particlePos.x - WhirlwindPos.x);

	v *= K;

	Vector3  r = v - p->getMeanVel();

	double coef = r.normalize();
	coef = _k1 * coef + _k2 * coef * coef;
	force = -r * coef;

	p->addForce(force);
}
