#include "ExplosionGenerator.h"
#include <cmath>
void ExplosionGenerator::updateForce(Particle* p, double t)
{


	if (fabs(1/p->getVariables().masa) < 1e-10)return;

	Vector3 forceDir{ 0,0,0 };
	Vector3 force;

	float r = pow(p->getMeanPos().x - center.x, 2)
		+ pow((p->getMeanPos().y - center.y), 2)
		+ pow((p->getMeanPos().z - center.z), 2);

	if (r < radio)
	{
		double a = K / pow(r, 2);
		double b = pow(e, -(t / explosion));

		forceDir = a * Vector3(p->getMeanPos().x - center.x, p->getMeanPos().y - center.y,
			p->getMeanPos().z - center.z) * b;

	}

	p->addForce(forceDir * p->getVariables().masa);





}
