#include "RigidWindGenerator.h"

void RigidWindGenerator::updateForce(RigidParticle* p, double t)
{
	if (_k2 == 0) {
		_k2 = airDensity * cD * p->getMass() * 4 * pi;
	}

	Vector3 v = p->getPxRigidDynamic()->getLinearVelocity() - windVel;
	float drag_coef = v.normalize();

	Vector3 dragForce;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;

	dragForce = -v * drag_coef;  //


	p->getPxRigidDynamic()->addForce(dragForce, PxForceMode::eIMPULSE);
}
