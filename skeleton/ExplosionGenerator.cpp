#include "ExplosionGenerator.h"
#include <cmath>
void ExplosionGenerator::updateForce(Particle* p, double t)
{


	if (fabs(1/p->getVariables().masa) < 1e-10)return;

	float r = sqrt(pow(p->getMeanPos().x - center.x, 2)
		+ pow((p->getMeanPos().y - center.y), 2)
		+ pow((p->getMeanPos().z - center.z), 2));
	if (r < radio)
	{
		float result = intensidad / pow(r, 2);
		Vector3 force{ result * (p->getMeanPos().x - center.x)
		 ,result * (p->getMeanPos().y - center.y)
		 ,result * (p->getMeanPos().z - center.z)
		};
		force *= exp(-(t / timeCt));
		p->addForce(force);
	}
	else
	{
		Vector3 force{ 0,0,0 };
		p->addForce(force);
	}





}
