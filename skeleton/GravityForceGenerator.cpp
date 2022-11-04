#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(1 / particle->getVariables().masa) < 1e-10)
		return;

	//Apply the mass scaled gravity
	particle->addForce(_gravity * particle->getVariables().masa);
}
