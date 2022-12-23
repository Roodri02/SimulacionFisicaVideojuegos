#include "RigidGravityForceGenerator.h"

RigidGravityForceGenerator::RigidGravityForceGenerator(const Vector3& g)
{
	_gravity = g;
}

void RigidGravityForceGenerator::updateForce(RigidParticle* particle, double t)
{
	//Apply the mass scaled gravity
	particle->getPxRigidDynamic()->addForce(_gravity * particle->getMass(), PxForceMode::eACCELERATION);
}