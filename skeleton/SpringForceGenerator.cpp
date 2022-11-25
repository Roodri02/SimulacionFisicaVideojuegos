#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
{
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

void SpringForceGenerator::updateForce(Particle* particle)
{

	Vector3 force = _other->getMeanPos() - particle->getMeanPos();


	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	particle->addForce(force);
}
