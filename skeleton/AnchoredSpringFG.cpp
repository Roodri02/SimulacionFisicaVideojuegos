#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr)
{
	_other = new Particle();

	_other->setParticle(1e6, 0, 50, { 0,0,0 }, anchor_pos, { 0,0,0 }, { 0.1,0.1,0.3,1 }, 1, { 0,0,0 }, { 0,0,0 }, false, true,
		CreateShape(physx::PxBoxGeometry(1, 1, 1)));
}
